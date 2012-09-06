#include "FBXLoader.h"
#include "Node.h"
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"
#include "Display.h"
#include "Texture.h"
#include "TGALoader.h"


FBXLoader::FBXLoader()
{
	this->Root = NULL;
	this->floor = 0;
}

FBXLoader::~FBXLoader()
{
	delete this->Root;
}

int	FBXLoader::Import(char* name)
{
	KFbxSdkManager* manage;
	KFbxIOSettings*	ios;
	KFbxImporter*	import;
	KFbxScene*	scene;
	KFbxNode*	root;
	int		i;
	Node*		Father;
	Scene*		sceneM;

	sceneM = Scene::GetInstance();
	i = 0;
	manage = KFbxSdkManager::Create();
	ios = 	KFbxIOSettings::Create(manage, IOSROOT);
	manage->SetIOSettings(ios);
	import = KFbxImporter::Create(manage, "");
	if (!import->Initialize(name, -1, manage->GetIOSettings()))
	{
		printf("initialize failed\nerror is %s\n",import->GetLastErrorString());
		return (42);
	}
	scene = KFbxScene::Create(manage, "MY SCENE");
	import->Import(scene);
	import->Destroy();
	root = scene->GetRootNode();
	if (root)
	{
		this->Root = new Node();
		this->Root->SetFather(NULL);
		this->Root->SetName("root");
		while (i < root->GetChildCount()) //papa
		{
			Father = new Node();
			Root->AddChild(Father);
			this->PrintNode(root->GetChild(i), Father);
			++i;
		}
	}
	sceneM->AddRoot(this->Root);
	manage->Destroy();
	return (0);
}

void	FBXLoader::PrintNode(KFbxNode* pNode, Node* node)
{
	KFbxNodeAttribute*	Patt;
	fbxDouble3		trans;
	fbxDouble3		rot;
	fbxDouble3		scale;
	const char*		nodeName;
	int			i;
	int			j;
	Node*			Child;
	Object*			obj;

	if (pNode == NULL)
		return;

	nodeName = pNode->GetName();
	trans = pNode->LclTranslation.Get();
	rot = pNode->LclRotation.Get();
	scale = pNode->LclScaling.Get();
	node->SetName(nodeName);
	node->SetTrans(trans);
	node->SetRot(rot);
	node->SetScale(scale);
	i = 0;
	while (i < pNode->GetNodeAttributeCount())
	{
		Patt = pNode->GetNodeAttributeByIndex(i);
		obj = GetAttributeTypeName(pNode, Patt->GetAttributeType());
		this->DisplayPivotsAndLimits(pNode, node);
		if (obj != NULL)
			node->AddObject(obj);
		++i;
	}
	j = 0;
	while (j < pNode->GetChildCount())	//fiston
	{
		Child = new Node();
		Child->SetFather(node);
		node->AddChild(Child);
		this->PrintNode(pNode->GetChild(j), Child);
		++j;
	}
}

Object*	FBXLoader::GetAttributeTypeName(KFbxNode* pNode, KFbxNodeAttribute::EAttributeType type)
{
	Object*			Obj;
	Camera*			Cam;
	fbxDouble3		trans;
	Scene*			scene;
	KFbxVector4		tmp;

	Obj = NULL;
	Cam = NULL;

//	tmp = new KFbxVector4();
//	if (strcmp(pNode->GetName(), "spawn") == 0)
//		std::cout<<"toto"<<std::endl;

	if (type == KFbxNodeAttribute::eUNIDENTIFIED)
	{
	//	std::cout<<"pNode->GetName() "<<pNode->GetName()<<std::endl;
		return (Obj);
	}
	else if (type == KFbxNodeAttribute::eNULL)
	{
		if (strcmp(pNode->GetName(), "spawn") == 0)
		{
			scene = Scene::GetInstance();
			trans = pNode->LclTranslation.Get();
			Cam =	new Camera();
			Cam->InitPos(trans[0], trans[1], trans[2]);
			scene->AddCam(Cam);
		}
		else if (strcmp(pNode->GetName(), "Camera001.Target") == 0)
		{
			scene = Scene::GetInstance();

		//	std::cout<<"size "<<
			
//			tmp[0] = trans[0] - (*scene->GetCamList())[2]->GetCam()->GetOriginX();
//			tmp[1] = trans[1] - (*scene->GetCamList())[2]->GetCam()->GetOriginY();
//			tmp[2] = trans[2] - (*scene->GetCamList())[2]->GetCam()->GetOriginZ();
//			tmp.Normalize();
//			(*scene->GetCamList())[2]->SetForw(tmp);
		}
		std::cout<<"pNode->GetName() "<<pNode->GetName()<<std::endl;
		trans = pNode->LclTranslation.Get();
		std::cout<<"x,y,z"<<trans[0]<<" "<<trans[0]<<" "<< trans[2]<<std::endl; 
		return (Obj);
	}
	else if (type == KFbxNodeAttribute::eMARKER)
		return (Obj);
	else if (type == KFbxNodeAttribute::eSKELETON)
		return (Obj);
	else if (type == KFbxNodeAttribute::eMESH)
	{
		Obj = this->ConstructBatch(pNode->GetMesh());
		return (Obj);
	}
	else if (type == KFbxNodeAttribute::eNURB)
		return (Obj);
	else if (type == KFbxNodeAttribute::ePATCH)
		return (Obj);
	else if (type == KFbxNodeAttribute::eCAMERA)
	{
		scene = Scene::GetInstance();
		trans = pNode->LclTranslation.Get();
		Cam = this->ConstructCamera(pNode);
//		std::cout<<"pNode->GetName() "<<pNode->GetName()<<std::endl;

		if (Cam != NULL)
		{
//			if (strcmp(pNode->GetName(), "spawn") == 0)
//				std::cout<<"toto"<<std::endl;
			std::cout<<"cam"<<std::endl;
			std::cout<<"x,y,z"<<trans[0]<<" "<<trans[0]<<" "<< trans[2]<<std::endl; 
			Cam->InitPos(trans[0], trans[1], trans[2]);
			tmp[0] =  (-36.8353) - trans[0];
			tmp[1] = (-36.8353) - trans[1];
			tmp[2] = 17.2166 - trans[2];
			tmp.Normalize();
			std::cout<<"tmp "<<tmp[0]<<" "<<tmp[1]<<" "<<tmp[2]<<std::endl;
			Cam->SetForw(tmp);
			scene->AddCam(Cam);
		}
		return (NULL);
	}
	else if (type == KFbxNodeAttribute::eCAMERA_STEREO)
		return (Obj);
	else if (type == KFbxNodeAttribute::eCAMERA_SWITCHER)
		return (Obj);
	else if (type == KFbxNodeAttribute::eLIGHT)
		return (Obj);
	else if (type == KFbxNodeAttribute::eOPTICAL_REFERENCE)
	{
		std::cout<<"pNode->GetName() "<<pNode->GetName()<<std::endl;
		return (Obj);
	}
	else if (type == KFbxNodeAttribute::eOPTICAL_MARKER)
		return (Obj);
	else if (type == KFbxNodeAttribute::eNURBS_CURVE)
		return (Obj);
	else if (type == KFbxNodeAttribute::eTRIM_NURBS_SURFACE)
		return (Obj);
	else if (type == KFbxNodeAttribute::eBOUNDARY)
		return (Obj);
	else if (type == KFbxNodeAttribute::eNURBS_SURFACE)
		return (Obj);
	else if (type == KFbxNodeAttribute::eSHAPE)
		return (Obj);
	else if (type == KFbxNodeAttribute::eLODGROUP)
		return (Obj);
	else if (type == KFbxNodeAttribute::eSUBDIV)
		return (Obj);
	return (Obj);
}

void	FBXLoader::PrintAll(void)
{
	std::cout << "Printing all node\n";
	size_t	i;
	size_t	end;

	i = 0;
	end = this->Root->GetChild()->size();
	std::cout<<Root->GetName()<<std::endl;
	while (i < end)
	{
		this->floor = 1;
		this->__PrintNode((*(this->Root->GetChild()))[i]);
		++i;
	}
}

void	FBXLoader::__PrintNode(Node* n)
{
	size_t	i;
	size_t	end;

	i = 0;
	while (i < this->floor)
	{
		std::cout << "\t";
		++i;
	}
	std::cout << n->GetName() << std::endl;
	i = 0;
	end = n->GetChild()->size();
	while (i < end)
	{
		++this->floor;
		this->__PrintNode((*(n->GetChild()))[i]);
		++i;
	}
	--this->floor;
}


ID_Mesh*	FBXLoader::ConstructBatch(KFbxMesh* mesh)
{
	_GLBatch*		batch;
	GLfloat*		v;
	int			i;
	int			nbpol;
	int			j;
	int			polsize;
	int			index;
	ID_Mesh*		obj;
	Display*		disp;
	int			VId;

	disp = Display::GetInstance();
	obj = new ID_Mesh(Mesh);
	i = 0;
	j = 0;
	VId = 0;
	nbpol = mesh->GetPolygonCount();
	v = new GLfloat[3];
	while (j < nbpol)
	{
		batch = new _GLBatch();
		i = 0;
		polsize = mesh->GetPolygonSize(j);
		batch->Begin(GL_POLYGON, polsize, 1);
		disp->NBTriangle += (polsize - 2);
		while (i < polsize)
		{
			
			index = mesh->GetPolygonVertex(j, i);
			this->GetVertexColor(mesh, VId, index);
			this->GetElementUV(mesh, i, j , batch);
			this->LoadNormal(index, VId, mesh, batch);

			this->GetBinormal(mesh);
			v[0] = mesh->mControlPoints[index][0];
			v[1] = mesh->mControlPoints[index][1];
			v[2] = mesh->mControlPoints[index][2];
			batch->Vertex3f(v[0], v[1], v[2]);
			++i;
			++VId;
		}
		++j;
		batch->End();
		obj->AddBatch(batch);

	}
	this->GetMaterial(mesh, obj);
	this->GetTexture(mesh, obj);
	this->GetMaterialConnection(mesh, obj);
	delete [] v;
	return (obj);
}


Camera*	FBXLoader::ConstructCamera(KFbxNode* node)
{
	KFbxCamera*	cam;
	GLfloat*	look;
	int		test;
	KFbxVector4	tmp;
	Camera*		camera;

	camera = new Camera();
	cam = (KFbxCamera*) node->GetNodeAttribute();
	look = new GLfloat[3];
	camera->SetWidth(cam->AspectWidth.Get());
	camera->SetHeight(cam->AspectHeight.Get());
	camera->SetFov(cam->FieldOfView.Get());
	camera->SetFar(cam->FarPlane.Get());
	camera->SetNear(cam->NearPlane.Get());
	camera->SetUpV(cam->UpVector.Get());
	look[0] = cam->InterestPosition.Get()[0];
	look[1] =  cam->InterestPosition.Get()[1]; 
	look[2] =  cam->InterestPosition.Get()[2];
	tmp[0] = look[0] - cam->Position.Get()[0];
	tmp[1] = look[1] - cam->Position.Get()[1];
	tmp[2] = look[2] - cam->Position.Get()[2];
	tmp.Normalize();
	camera->SetForw(tmp);
	if (cam->ProjectionType.Get() == KFbxCamera::eORTHOGONAL)
		test = 0;
	else
		test = 1;
	delete [] look;
	return (camera);
}

void	FBXLoader::GetElementUV(KFbxMesh* m, int i, int j, _GLBatch* b)
{
	int	l;
	l = 0;
	while (l < m->GetElementUVCount())
	{
		KFbxGeometryElementUV*	uv;

		uv = m->GetElementUV(l);
		switch ((int)uv->GetMappingMode())
		{
			case KFbxGeometryElement::eBY_CONTROL_POINT:
				switch (uv->GetReferenceMode())
				{
					case KFbxGeometryElement::eDIRECT:
						break;
					case KFbxGeometryElement::eINDEX_TO_DIRECT:
						break;
					default:
						break;
				}
				break;
			case KFbxGeometryElement::eBY_POLYGON_VERTEX:
			{
				int	uv_id;

				uv_id = m->GetTextureUVIndex(j, i);
				switch (uv->GetReferenceMode())
				{
					case KFbxGeometryElement::eDIRECT:
						break;
					case KFbxGeometryElement::eINDEX_TO_DIRECT:
					{
						b->MultiTexCoord2f(0, uv->GetDirectArray().GetAt(uv_id)[0],
								   uv->GetDirectArray().GetAt(uv_id)[1]);
					}
						break;
					default:
						break;
				}
			}
			break;
			case KFbxGeometryElement::eBY_POLYGON:
			case KFbxGeometryElement::eALL_SAME:
			case KFbxGeometryElement::eNONE:
				break;
		}
		++l;
	}
}



void FBXLoader::LoadNormal(int id, int vertexId, KFbxMesh* pMesh, _GLBatch* B)
{
	for(int  l = 0; l < pMesh->GetElementNormalCount(); ++l)
	{
		KFbxGeometryElementNormal* leNormal = pMesh->GetElementNormal( l);
		if(leNormal->GetMappingMode() == KFbxGeometryElement::eBY_POLYGON_VERTEX)
		{
			switch (leNormal->GetReferenceMode())
			{
				case KFbxGeometryElement::eDIRECT:
					B->Normal3f((leNormal->GetDirectArray().GetAt(vertexId))[0],
						    (leNormal->GetDirectArray().GetAt(vertexId))[1],
						    (leNormal->GetDirectArray().GetAt(vertexId))[2]);
					break;
				case KFbxGeometryElement::eINDEX_TO_DIRECT:
					{
						int _id;
						_id = leNormal->GetIndexArray().GetAt(vertexId);
						B->Normal3f((leNormal->GetDirectArray().GetAt(id))[0], 
							    (leNormal->GetDirectArray().GetAt(id))[1],
							    (leNormal->GetDirectArray().GetAt(id))[2]);
					}
					break;
				default:
					break; // other reference modes not shown here!
			}
		}
	}
}

bool	FBXLoader::GetMaterial(KFbxGeometry* g, Object* o)
{
	int		m_count;
	KFbxNode*	n;

	m_count = 0;
	n = NULL;
	if (g)
	{
		n = g->GetNode();
		if (n)
			m_count = n->GetMaterialCount();
	}
	if (m_count > 0)
	{
		KFbxPropertyDouble3	double3;
		KFbxPropertyDouble1	double1;
		KFbxColor		col;
		Material*		mat;
		int			i;

		i = 0;
		while (i < m_count)
		{
			KFbxSurfaceMaterial*		_mat;
			const KFbxImplementation*	imp;
			KString				imp_type;

			_mat = n->GetMaterial(i);
			mat = new (std::nothrow) Material;
			if (mat == NULL)
			{
				std::cout << "[FbxLoader]{__GetMaterial} Error: Can not allocate memory \n";
				return (false);
			}
			mat->SetName((char*)_mat->GetName());
			imp = GetImplementation(_mat, ImplementationHLSL);
			imp_type = "HLSL";
			if (!imp)
			{
				imp = GetImplementation(_mat, ImplementationCGFX);
				imp_type = "CGFX";
			}
			if (_mat->GetClassId().Is(KFbxSurfacePhong::ClassId))
			{
				double3 = ((KFbxSurfacePhong*)_mat)->Ambient;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);

				Color Amb(double3);
				mat->SetAmbient(Amb);
				double3 = ((KFbxSurfacePhong*)_mat)->Diffuse;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);
				Color Diff(double3);
				mat->SetDiffuse(Diff);
				double3 = ((KFbxSurfacePhong*)_mat)->Specular;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);
				Color Spec(double3);
				mat->SetSpecular(Spec);
				double3 = ((KFbxSurfacePhong*)_mat)->Emissive;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);
				Color Em(double3);
				mat->SetEmissive(Em);
				double1 = ((KFbxSurfacePhong*)_mat)->TransparencyFactor;
				mat->SetOpacity(1.0 - double1.Get());
				double1 = ((KFbxSurfacePhong*)_mat)->Shininess;
				mat->SetShininess(double1.Get());
				double1 = ((KFbxSurfacePhong*)_mat)->ReflectionFactor;
				mat->SetReflection(1.0 - double1.Get());
				mat->SetShadingModel(1);
			}
			else if (_mat->GetClassId().Is(KFbxSurfaceLambert::ClassId))
			{
				double3 = ((KFbxSurfaceLambert*)_mat)->Ambient;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);
				Color Amb(double3);
				mat->SetAmbient(Amb);
				double3 = ((KFbxSurfaceLambert*)_mat)->Diffuse;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);
				Color Diff(double3);
				mat->SetDiffuse(Diff);
				double3 = ((KFbxSurfaceLambert*)_mat)->Emissive;
				col.Set(double3.Get()[0], double3.Get()[1], double3.Get()[2]);
				Color Em(double3);
				mat->SetEmissive(Em);
				double1 = ((KFbxSurfaceLambert*)_mat)->TransparencyFactor;
				mat->SetOpacity(1.0 - double1.Get());
				mat->SetShadingModel(2);
			}
			o->AddMaterial(mat);
			++i;
		}
	}
	return (true);
}

void	FBXLoader::GetBinormal(KFbxMesh* m)
{
	int	l;
	l = 0;
	while (l < m->GetElementBinormalCount())
	{
		KFbxGeometryElementBinormal*	bi;

		bi = m->GetElementBinormal(l);
		if (bi->GetMappingMode() == KFbxGeometryElement::eBY_POLYGON_VERTEX)
		{
			switch (bi->GetReferenceMode())
			{
				case KFbxGeometryElement::eDIRECT:
					break;
				case KFbxGeometryElement::eINDEX_TO_DIRECT:
					break;
				default:
					break;
			}
		}
		++l;
	}
}

void	FBXLoader::GetVertexColor(KFbxMesh* m, int vertexId, int id)
{
	int	l;

	l = 0;
	while (l < m->GetElementVertexColorCount())
	{
		KFbxGeometryElementVertexColor*	Vtxc;

		Vtxc = m->GetElementVertexColor(l);
		switch ((int)Vtxc->GetMappingMode())
		{
			case KFbxGeometryElement::eBY_CONTROL_POINT:
				switch (Vtxc->GetReferenceMode())
				{
					case KFbxGeometryElement::eDIRECT:
						break;
					case KFbxGeometryElement::eINDEX_TO_DIRECT:
					{
						int	_id;

						_id = Vtxc->GetIndexArray().GetAt(id);
					}
						break;
					default:
						break;
				}
				break;
			case KFbxGeometryElement::eBY_POLYGON_VERTEX:
			{
				switch (Vtxc->GetReferenceMode())
				{
					case KFbxGeometryElement::eDIRECT:
						break;
					case KFbxGeometryElement::eINDEX_TO_DIRECT:
					{
						int	_id;

						_id = Vtxc->GetIndexArray().GetAt(vertexId);
					}
						break;
					default:
						break;
				}
			}
			break;
			case KFbxGeometryElement::eBY_POLYGON:
			case KFbxGeometryElement::eALL_SAME:
			case KFbxGeometryElement::eNONE:
				break;
		}
		++l;
	}
}


bool	FBXLoader::DisplayTextureNames( KFbxProperty &pProperty, KString& pConnectionString)
{
	int lLayeredTextureCount = pProperty.GetSrcObjectCount(KFbxLayeredTexture::ClassId);
	if (lLayeredTextureCount > 0)
	{
		for (int j=0; j<lLayeredTextureCount; ++j)
		{
			KFbxLayeredTexture *lLayeredTexture = KFbxCast <KFbxLayeredTexture>(pProperty.GetSrcObject(KFbxLayeredTexture::ClassId, j));
			int lNbTextures = lLayeredTexture->GetSrcObjectCount(KFbxTexture::ClassId);
			pConnectionString += " Texture ";

			for (int k =0; k<lNbTextures; ++k)
			{
				pConnectionString += "\"";
				pConnectionString += (char*)lLayeredTexture->GetName();
				pConnectionString += "\"";
				pConnectionString += " ";
			}
			pConnectionString += "of ";
			pConnectionString += pProperty.GetName();
			pConnectionString += " on layer ";
			pConnectionString += j;
		}
		pConnectionString += " |";
		return true;
	}
	else
	{
		int lNbTextures = pProperty.GetSrcObjectCount(KFbxTexture::ClassId);

		if (lNbTextures > 0)
		{
			pConnectionString += " Texture ";
			pConnectionString += " ";

			for (int j =0; j<lNbTextures; ++j)
			{
				KFbxTexture* lTexture = KFbxCast <KFbxTexture> (pProperty.GetSrcObject(KFbxTexture::ClassId,j));
				if (lTexture)
				{
					pConnectionString += "\"";
					pConnectionString += (char*)lTexture->GetName();
					pConnectionString += "\"";
					pConnectionString += " ";
				}
			}
			pConnectionString += "of ";
			pConnectionString += pProperty.GetName();
			pConnectionString += " |";
			return true;
		}
		return false;
	}
}

void	FBXLoader::GetMaterialConnection(KFbxMesh* m, Object* o)
{
	int	i;
	int	l;
	int	p_count;
	char	h[200];
	bool	same;
	(void)h;

	same = true;
	p_count = m->GetPolygonCount();
	l = 0;
	while (l < m->GetElementMaterialCount())
	{
		KFbxGeometryElementMaterial*	m_el;
		
		m_el = m->GetElementMaterial(l);
		if (m_el->GetMappingMode() == KFbxGeometryElement::eBY_POLYGON)
		{
			same = false;
			break;
		}
		++l;
	}
	if (same)
	{
		l = 0;
		while (l < m->GetElementMaterialCount())
		{
			KFbxGeometryElementMaterial*	m_el;

			m_el = m->GetElementMaterial(l);
			if (m_el->GetMappingMode() == KFbxGeometryElement::eALL_SAME)
			{
				KFbxSurfaceMaterial*	_mat;
				int			mat_id;

				_mat = m->GetNode()->GetMaterial(m_el->GetIndexArray().GetAt(0));
				mat_id = m_el->GetIndexArray().GetAt(0);
				if (mat_id >= 0)
					this->GetMaterialTextureConnection(_mat, h, mat_id, l, NULL);
			}
			++l;
		}
	}
	else
	{
		i = 0;
		while (i < p_count)
		{
			l = 0;
			while (l < m->GetElementMaterialCount())
			{
				KFbxGeometryElementMaterial*	m_el;
				KFbxSurfaceMaterial*		_mat;
				int				mat_id;

				mat_id = -1;
				_mat = NULL;
				m_el = m->GetElementMaterial(l);
				_mat = m->GetNode()->GetMaterial(m_el->GetIndexArray().GetAt(i));
				mat_id = m_el->GetIndexArray().GetAt(i);
				if (mat_id >= 0)
				{
					(*((ID_Mesh*)o)->GetMesh())[i]->SetMatIndex(mat_id);
					this->GetMaterialTextureConnection(_mat, h, mat_id, l, (*((ID_Mesh*)o)->GetMesh())[i]);
				}
				else
					(*((ID_Mesh*)o)->GetMesh())[i]->SetMatIndex(-1);
				++l;
			}
			++i;
		}
	}
}


bool	FBXLoader::GetMaterialTextureConnection(KFbxSurfaceMaterial* _mat, char* h, int mat_id, int l, _GLBatch* b)
{
	(void)l;
	(void)h;
	(void)mat_id;
	if (_mat == NULL)
		return (true);
	KFbxProperty	prop;
	KString		lConnectionString = "            Material %d -- ";

	prop= _mat->FindProperty(KFbxSurfaceMaterial::sDiffuse);
	if (DisplayTextureNames(prop, lConnectionString))
	{
		if (b != NULL)
			b->SetTextDiffIndex(1);
	}
	return (true);
}



bool	FBXLoader::GetTexture(KFbxGeometry* g, Object* o)
{
	int		mat_i;
	KFbxProperty	prop;
	int		mat_nb;

	if (g == NULL)
		return (false);
	mat_nb = g->GetNode()->GetSrcObjectCount(KFbxSurfaceMaterial::ClassId);
	mat_i = 0;
	while (mat_i < mat_nb)
	{
		KFbxSurfaceMaterial*	_mat;
		bool			disp;

		disp = true;
		_mat = (KFbxSurfaceMaterial*)g->GetNode()->GetSrcObject(KFbxSurfaceMaterial::ClassId, mat_i);
		if (_mat)
		{
			int	tex_i;

			FOR_EACH_TEXTURE(tex_i)
			{
				prop = _mat->FindProperty(KFbxLayerElement::TEXTURE_CHANNEL_NAMES[tex_i]);
				this->FindTextureInfo(prop, disp, mat_i, o);
			}
		}
		++mat_i;
	}
	return (true);
}


bool	FBXLoader::FindTextureInfo(KFbxProperty prop, bool& disp, int mat_i, Object* o)
{
	if (prop.IsValid())
	{
		Texture*	t;

		t = new (std::nothrow) Texture;
		if (t == NULL)
		{
			std::cout << "[FbxLoader]{__FindTextureInfo} Error: Can not allocate memory\n";
			return (false);
		}
		int	t_count;
		int	i;

		t_count = prop.GetSrcObjectCount(KFbxTexture::ClassId);
		i = 0;
		while (i < t_count)
		{
			KFbxLayeredTexture*	lay_t;

			lay_t = KFbxCast <KFbxLayeredTexture>(prop.GetSrcObject(KFbxLayeredTexture::ClassId, i));
			if (lay_t)
			{
				KFbxLayeredTexture*	lay_t2;
				int			nb_text;
				int			j;

				lay_t2 = KFbxCast <KFbxLayeredTexture>(prop.GetSrcObject(KFbxLayeredTexture::ClassId, i));
				nb_text = lay_t2->GetSrcObjectCount(KFbxTexture::ClassId);
				j = 0;
				while (j < nb_text)
				{
					KFbxTexture*	_t;

					_t = KFbxCast <KFbxTexture> (lay_t2->GetSrcObject(KFbxTexture::ClassId, j));
					if (_t)
					{
						KFbxLayeredTexture::EBlendMode blend_mode;

						if (disp)
							disp = false;
						lay_t2->GetTextureBlendMode(j, blend_mode);
						this->TextureInfoFinded(_t, (int)blend_mode, t);
						o->GetMatList()->at(mat_i)->AddTexture(t);
					}
					++j;
				}
			}
			else
			{
				KFbxTexture*	_t;

				_t = KFbxCast <KFbxTexture> (prop.GetSrcObject(KFbxTexture::ClassId, i));
				if (_t)
				{
					if (disp)
						disp = false;
					if (strcmp(prop.GetName(), "DiffuseColor") == 0)
						t->SetTXTChanel(0);
					else if (strcmp(prop.GetName(), "SpecularColor") == 0)
						t->SetTXTChanel(3);
					this->TextureInfoFinded(_t, -1, t);
					o->GetMatList()->at(mat_i)->AddTexture(t);
				}
			}
			++i;
		}
	}
	return (true);
}


void	FBXLoader::TextureInfoFinded(KFbxTexture* _t, int blend_mode, Texture* t)
{
	KFbxFileTexture*	f_text;
	KFbxProceduralTexture*	pro_text;
	GLuint			text_id;
	TGAReader		reader;

	(void)blend_mode;
	f_text = KFbxCast <KFbxFileTexture>(_t);
	pro_text = KFbxCast <KFbxProceduralTexture>(_t);

	t->SetName((char*)_t->GetName());
	if (f_text)
	{
		t->SetFilename((char*)f_text->GetFileName());
		glGenTextures(1, &text_id);
		glBindTexture(GL_TEXTURE_2D, text_id);
		if (reader.ReadFile(t->GetFileName(), GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE))
			t->SetID(text_id);
		else
			glDeleteTextures(1, &text_id);
	}
	t->SetTXTUse(_t->GetTextureUse());
}


void FBXLoader::DisplayPivotsAndLimits(KFbxNode* pNode, Node* node)
{
	KFbxVector4 lTmpVector;

	//
	// Pivots
	//
//	printf("    Pivot Information\n");

	KFbxNode::EPivotState lPivotState;
	pNode->GetPivotState(KFbxNode::eSOURCE_SET, lPivotState);
//	printf("        Pivot State: %s\n", lPivotState == KFbxNode::ePIVOT_STATE_ACTIVE ? "Active" : "Reference");

	lTmpVector = pNode->GetPreRotation(KFbxNode::eSOURCE_SET);
//	printf("        Pre-Rotation: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
	node->SetPreRot(lTmpVector);
	lTmpVector = pNode->GetPostRotation(KFbxNode::eSOURCE_SET);
//	printf("        Post-Rotation: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

	lTmpVector = pNode->GetRotationPivot(KFbxNode::eSOURCE_SET);
//	printf("        Rotation Pivot: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

	lTmpVector = pNode->GetRotationOffset(KFbxNode::eSOURCE_SET);
//	printf("        Rotation Offset: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

	lTmpVector = pNode->GetScalingPivot(KFbxNode::eSOURCE_SET);
//	printf("        Scaling Pivot: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
//
	lTmpVector = pNode->GetScalingOffset(KFbxNode::eSOURCE_SET);
//	printf("        Scaling Offset: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

	//
	// Limits
	//
	KFbxNodeLimits lLimits = pNode->GetLimits();
	bool           lIsActive, lMinXActive, lMinYActive, lMinZActive;
	bool           lMaxXActive, lMaxYActive, lMaxZActive;
	KFbxVector4    lMinValues, lMaxValues;

//	printf("    Limits Information\n");

	lIsActive = lLimits.GetTranslationLimitActive();
	lLimits.mTranslationLimits.GetLimitMinActive(lMinXActive, lMinYActive, lMinZActive);
	lLimits.mTranslationLimits.GetLimitMaxActive(lMaxXActive, lMaxYActive, lMaxZActive);
	lMinValues = lLimits.mTranslationLimits.GetLimitMin();
	lMaxValues = lLimits.mTranslationLimits.GetLimitMax();

//	printf("        Translation limits: %s\n", lIsActive ? "Active" : "Inactive");
//	printf("            X\n");
//	printf("                Min Limit: %s\n", lMinXActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[0]);
//	printf("                Max Limit: %s\n", lMaxXActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[0]);
//	printf("            Y\n");
//	printf("                Min Limit: %s\n", lMinYActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[1]);
//	printf("                Max Limit: %s\n", lMaxYActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[1]);
//	printf("            Z\n");
//	printf("                Min Limit: %s\n", lMinZActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[2]);
//	printf("                Max Limit: %s\n", lMaxZActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[2]);

	lIsActive = lLimits.GetRotationLimitActive();
	lLimits.mRotationLimits.GetLimitMinActive(lMinXActive, lMinYActive, lMinZActive);
	lLimits.mRotationLimits.GetLimitMaxActive(lMaxXActive, lMaxYActive, lMaxZActive);
	lMinValues = lLimits.mRotationLimits.GetLimitMin();
	lMaxValues = lLimits.mRotationLimits.GetLimitMax();

//	printf("        Rotation limits: %s\n", lIsActive ? "Active" : "Inactive");
//	printf("            X\n");
//	printf("                Min Limit: %s\n", lMinXActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[0]);
//	printf("                Max Limit: %s\n", lMaxXActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[0]);
///	printf("            Y\n");
//	printf("                Min Limit: %s\n", lMinYActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[1]);
//	printf("                Max Limit: %s\n", lMaxYActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[1]);
//	printf("            Z\n");
//	printf("                Min Limit: %s\n", lMinZActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[2]);
//	printf("                Max Limit: %s\n", lMaxZActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[2]);

	lIsActive = lLimits.GetScalingLimitActive();
	lLimits.mScalingLimits.GetLimitMinActive(lMinXActive, lMinYActive, lMinZActive);
	lLimits.mScalingLimits.GetLimitMaxActive(lMaxXActive, lMaxYActive, lMaxZActive);
	lMinValues = lLimits.mScalingLimits.GetLimitMin();
	lMaxValues = lLimits.mScalingLimits.GetLimitMax();

//	printf("        Scaling limits: %s\n", lIsActive ? "Active" : "Inactive");
//	printf("            X\n");
//	printf("                Min Limit: %s\n", lMinXActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[0]);
//	printf("                Max Limit: %s\n", lMaxXActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[0]);
//	printf("            Y\n");
//	printf("                Min Limit: %s\n", lMinYActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[1]);
//	printf("                Max Limit: %s\n", lMaxYActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[1]);
//	printf("            Z\n");
//	printf("                Min Limit: %s\n", lMinZActive ? "Active" : "Inactive");
//	printf("                Min Limit Value: %f\n", lMinValues[2]);
//	printf("                Max Limit: %s\n", lMaxZActive ? "Active" : "Inactive");
//	printf("                Max Limit Value: %f\n", lMaxValues[2]);
}

