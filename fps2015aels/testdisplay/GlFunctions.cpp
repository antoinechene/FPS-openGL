#include <math.h>
#include <fbxsdk.h>
#include "GL/glut.h"
#include <fbxfilesdk/fbxfilesdk_nsuse.h>
#include "GlFunctions.h"
#include "Texture.h"

extern ShadingManager * gShadingManager;

void GlGetWindowSize(int& pWidth, int& pHeight)
{
	pWidth = glutGet(GLUT_WINDOW_WIDTH);
	pHeight = glutGet(GLUT_WINDOW_HEIGHT);      
}


void GlSetCameraPerspective(double pFieldOfViewY,
		double pAspect,
		double pNearPlane,
		double pFarPlane,
		KFbxVector4& pEye,
		KFbxVector4& pCenter,
		KFbxVector4& pUp)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	gluPerspective(pFieldOfViewY, 
			pAspect, 
			pNearPlane, 
			pFarPlane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pEye[0], pEye[1], pEye[2],
			pCenter[0], pCenter[1], pCenter[2],
			pUp[0], pUp[1], pUp[2]);
}


void GlSetCameraOrthogonal(double pLeftPlane,
		double pRightPlane,
		double pBottomPlane,
		double pTopPlane,
		double pNearPlane,
		double pFarPlane,
		KFbxVector4& pEye,
		KFbxVector4& pCenter,
		KFbxVector4& pUp)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	glOrtho(pLeftPlane, 
			pRightPlane, 
			pBottomPlane, 
			pTopPlane, 
			pNearPlane, 
			pFarPlane); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pEye[0], pEye[1], pEye[2],
			pCenter[0], pCenter[1], pCenter[2],
			pUp[0], pUp[1], pUp[2]);
}


void GlDrawMarker(KFbxXMatrix& pGlobalPosition)
{
	glColor3f(0.0, 1.0, 1.0);
	glLineWidth(1.0);

	glPushMatrix();
	glMultMatrixd((double*) pGlobalPosition);

	glutWireCube(2.0);

	glPopMatrix();
}


void GlDrawLimbNode(KFbxXMatrix& pGlobalBasePosition, KFbxXMatrix& pGlobalEndPosition)
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);

	glBegin(GL_LINES);

	glVertex3dv((GLdouble *)pGlobalBasePosition.GetT());
	glVertex3dv((GLdouble *)pGlobalEndPosition.GetT());

	glEnd();
}


void GlDrawMesh(const KFbxXMatrix& pGlobalPosition, const KFbxMesh* pMesh, const KFbxVector4* pVertexArray)
{
	ShadingManager::ShadingMode lDrawMode = gShadingManager->GetShadingMode();
	if (pMesh->GetNode()->GetMaterialCount() == 0)
		lDrawMode = ShadingManager::SHADING_MODE_WIREFRAME;

	const int lGLPrimitive = lDrawMode == ShadingManager::SHADING_MODE_WIREFRAME ? GL_LINE_LOOP : GL_POLYGON;

	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1.0);

	glPushMatrix();
	glMultMatrixd((const double*)pGlobalPosition);

	const bool lHasNormal = pMesh->GetElementNormalCount() > 0;
	const bool lHasUV = pMesh->GetElementUVCount() > 0;
	KStringList lUVNames;
	pMesh->GetUVSetNames(lUVNames);
	KFbxLayerElementArrayTemplate<int>* lMaterialIndice = NULL;
	KFbxGeometryElement::EMappingMode lMaterialMappingMode = KFbxGeometryElement::eNONE;

	if (lDrawMode == ShadingManager::SHADING_MODE_SHADED)
	{
		if (pMesh->GetElementMaterial())
		{
			pMesh->GetMaterialIndices(&lMaterialIndice);
			lMaterialMappingMode = pMesh->GetElementMaterial()->GetMappingMode();
		}

		if (lHasNormal)
		{
			glEnable(GL_NORMALIZE);
		}

		if (lHasUV)
		{
			glEnable(GL_TEXTURE_2D);
		}

		glEnable(GL_LIGHTING);
	}

	if (lDrawMode == ShadingManager::SHADING_MODE_SHADED)
	{
		if (lMaterialMappingMode == KFbxGeometryElement::eNONE)
		{
			gShadingManager->SetMaterial(pMesh->GetNode(), 0);
		}
		else if (lMaterialMappingMode == KFbxGeometryElement::eALL_SAME && lMaterialIndice)
		{
			gShadingManager->SetMaterial(pMesh->GetNode(), lMaterialIndice->GetAt(0));
		}
	}

	KFbxVector2 lCurrentUV;
	KFbxVector4 lCurrentNormal;
	const int lPolygonCount = pMesh->GetPolygonCount();
	for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex)
	{
		if (lDrawMode == ShadingManager::SHADING_MODE_SHADED && lMaterialMappingMode == KFbxGeometryElement::eBY_POLYGON)
		{
			const int lMaterialIndex = lMaterialIndice->GetAt(lPolygonIndex);
			gShadingManager->SetMaterial(pMesh->GetNode(), lMaterialIndex);
		}

		glBegin(lGLPrimitive);

		const int lVerticeCount = pMesh->GetPolygonSize(lPolygonIndex);
		for (int lVerticeIndex = 0; lVerticeIndex < lVerticeCount; ++lVerticeIndex)
		{
			if (lDrawMode == ShadingManager::SHADING_MODE_SHADED)
			{
				if (lHasUV && pMesh->GetPolygonVertexUV(lPolygonIndex, lVerticeIndex, lUVNames[0].Buffer(), lCurrentUV))
				{
					glTexCoord2dv(lCurrentUV.mData);
				}

				if (lHasNormal && pMesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, lCurrentNormal))
				{
					glNormal3d(lCurrentNormal[0], lCurrentNormal[1], lCurrentNormal[2]);
				}
			}

			glVertex3dv((const GLdouble *)pVertexArray[pMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)]);
		}

		glEnd();
	}

	if (lDrawMode == ShadingManager::SHADING_MODE_SHADED)
	{
		glDisable(GL_LIGHTING);

		if (lHasUV)
		{
			glDisable(GL_TEXTURE_2D);
		}

		if (lHasNormal)
		{
			glDisable(GL_NORMALIZE);
		}
	}

	if (gShadingManager->IsDrawNormal())
	{
		GLfloat lCurrentColor[4];
		glGetFloatv(GL_CURRENT_COLOR, lCurrentColor);

		glColor3f(0.5f, 0.5f, 0.0f);
		KFbxVector4 lCurrentNormal;
		const int lPolygonCount = pMesh->GetPolygonCount();
		for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex)
		{
			glBegin(GL_LINES);
			const int lVerticeCount = pMesh->GetPolygonSize(lPolygonIndex);
			for (int lVerticeIndex = 0; lVerticeIndex < lVerticeCount; ++lVerticeIndex)
			{
				const KFbxVector4 p1 = pVertexArray[pMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)];
				pMesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, lCurrentNormal);
				lCurrentNormal.Normalize();
				const double lNormalScale = gShadingManager->GetNormalScale();
				const KFbxVector4 p2 = p1 + lCurrentNormal * lNormalScale;
				glVertex3dv(p1);
				glVertex3dv(p2);
			}
			glEnd();
		}

		glColor4fv(lCurrentColor);
	}
	glPopMatrix();
}


void GlDrawCamera(KFbxXMatrix& pGlobalPosition, double pRoll)
{
	glColor3d(1.0, 1.0, 1.0);
	glLineWidth(1.0);

	glPushMatrix();
	glMultMatrixd((double*) pGlobalPosition);
	glRotated(pRoll, 1.0, 0.0, 0.0);

	int i;
	float lCamera[10][2] = {{ 0, 5.5 }, { -3, 4.5 },
		{ -3, 7.5 }, { -6, 10.5 }, { -23, 10.5 },
		{ -23, -4.5 }, { -20, -7.5 }, { -3, -7.5 },
		{ -3, -4.5 }, { 0, -5.5 }   };

	glBegin( GL_LINE_LOOP );
	{
		for (i = 0; i < 10; i++)
		{
			glVertex3f(lCamera[i][0], lCamera[i][1], 4.5);
		}
	}
	glEnd();

	glBegin( GL_LINE_LOOP );
	{
		for (i = 0; i < 10; i++)
		{
			glVertex3f(lCamera[i][0], lCamera[i][1], -4.5);
		}
	}
	glEnd();

	for (i = 0; i < 10; i++)
	{
		glBegin( GL_LINES );
		{
			glVertex3f(lCamera[i][0], lCamera[i][1], -4.5);
			glVertex3f(lCamera[i][0], lCamera[i][1], 4.5);
		}
		glEnd();
	}

	glPopMatrix();
}


void GlDrawLight(const KFbxXMatrix& pGlobalPosition, const KFbxLight* pLight,
		const KFbxColor& pColor, double pConeAngle)
{
	glColor3d(pColor.mRed, pColor.mGreen, pColor.mBlue);
	glLineWidth(1.0);

	glPushMatrix();
	glMultMatrixd((const double*)pGlobalPosition);

	if (pLight->LightType.Get() == KFbxLight::eSPOT)
	{
		const double lRadians = 3.1416 * pConeAngle / 180.0;
		const double lHeight = 15.0;
		const double lBase = lHeight * tan(lRadians / 2);
		glutWireCone(lBase, lHeight, 18, 1);
	}
	else
	{
		glutWireSphere(1.0, 10, 10);
	}

	gShadingManager->SetLight(pLight->LightType.Get(), pColor, pConeAngle);

	glPopMatrix();
}


void GlDrawCrossHair(KFbxXMatrix& pGlobalPosition)
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);

	glPushMatrix();
	glMultMatrixd((double*) pGlobalPosition);

	double lCrossHair[6][3] = { { -3, 0, 0 }, { 3, 0, 0 },
		{ 0, -3, 0 }, { 0, 3, 0 },
		{ 0, 0, -3 }, { 0, 0, 3 } };

	glBegin(GL_LINES);

	glVertex3dv(lCrossHair[0]);
	glVertex3dv(lCrossHair[1]);

	glEnd();

	glBegin(GL_LINES);

	glVertex3dv(lCrossHair[2]);
	glVertex3dv(lCrossHair[3]);

	glEnd();

	glBegin(GL_LINES);

	glVertex3dv(lCrossHair[4]);
	glVertex3dv(lCrossHair[5]);

	glEnd();

	glPopMatrix();
}

void GlDrawGrid(KFbxXMatrix& pGlobalPosition)
{
	glPushMatrix();
	glMultMatrixd((double*) pGlobalPosition);

	glColor3f(0.3, 0.3, 0.3);
	glLineWidth(1.0);
	const int hw = 500;
	const int step = 20;
	const int bigstep = 100;
	int       i;

	for (i = -hw; i <= hw; i+=step) {

		if (i % bigstep == 0) {
			glLineWidth(2.0);
		} else {
			glLineWidth(1.0);
		}
		glBegin(GL_LINES);
		glVertex3f(i,0,-hw);
		glVertex3f(i,0,hw);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-hw,0,i);
		glVertex3f(hw,0,i);
		glEnd();

	}

	const int zoffset = -2;
	const int xoffset = 1;
	for (i = -hw; i <= hw; i+=bigstep) {

		KString scoord;
		int is, lCount;

		if (i == 0) {
			scoord = "0";
			lCount = (int)scoord.GetLen();
			glPushMatrix();
			glTranslatef(i+xoffset,0,zoffset);
			glRotatef(-90,1,0,0);
			glScalef(.03,.03,.03);
			for (is = 0; is < lCount; is++) {
				char lC = scoord.Buffer()[is];
				glutStrokeCharacter(GLUT_STROKE_ROMAN, lC);
			}
			glPopMatrix();

			continue;
		}

		// X coordinates
		scoord = "X: ";
		scoord += i;
		lCount = (int)scoord.GetLen();

		glPushMatrix();
		glTranslatef(i+xoffset,0,zoffset);
		glRotatef(-90,1,0,0);
		glScalef(.03,.03,.03);
		for (is = 0; is < lCount; is++) {
			char lC = scoord.Buffer()[is];
			glutStrokeCharacter(GLUT_STROKE_ROMAN, lC);
		}
		glPopMatrix();

		// Z coordinates
		scoord = "Z: ";
		scoord += i;
		lCount = (int)scoord.GetLen();

		glPushMatrix();
		glTranslatef(xoffset,0,i+zoffset);
		glRotatef(-90,1,0,0);
		glScalef(.03,.03,.03);
		for (is = 0; is < lCount; is++) {
			char lC = scoord.Buffer()[is];
			glutStrokeCharacter(GLUT_STROKE_ROMAN, lC);
		}
		glPopMatrix();

	}

	glPopMatrix();
}

