#include <fbxsdk.h>
#include <math.h>
#include "GL/glut.h"
#include <fbxfilesdk/fbxfilesdk_nsuse.h>
#include "InitScene.h"
#include "SetCamera.h"
#include "DrawScene.h"
#include "Texture.h"
#include "Common.h"

void CreateMenus();
void CameraSelectionCallback(int pItem);
void AnimStackSelectionCallback(int pItem);
void ShadingModeSelectionCallback(int pItem);
void TimerCallback(int);
void DisplayCallback();
void ReshapeCallback(int pWidth, int pHeight);
void KeyboardCallback(unsigned char pKey, int, int);
void MouseCallback(int button, int state, int x, int y);
void MotionCallback(int x, int y);

KString ExtractDirectory(KString pFilePath);

// Global variables.
KFbxSdkManager* gSdkManager;
KFbxImporter* gImporter;

KFbxScene* gScene;
KFbxAnimStack* gCurrentAnimationStack; 
KFbxAnimLayer* gCurrentAnimationLayer; // This is the animation layer that is currently active and where
// the animation curves are extracted from
int gSceneStatus;
ShadingManager * gShadingManager;

template<class KString> 
class DeletionPolicy
{
	public:
		static inline void DeleteIt(KString** ptr) 
		{
			if ( *ptr != NULL )
			{
				delete *ptr;
				*ptr = NULL;
			}
		}
};

KScopedPtr<KString, DeletionPolicy<KString> > gWindowMessage;
KScopedPtr<KString, DeletionPolicy<KString> > gFileName;

KArrayTemplate<KFbxNode*>  gCameraArray;
KArrayTemplate<KString*>   gAnimStackNameArray;
KArrayTemplate<KFbxPose*>  gPoseArray;
KTime gPeriod, gStart, gStop, gCurrentTime;
int gPoseIndex;
int gX, gY;
KFbxVector4 gCamPosition, gCamCenter;
double gRoll;
int gCameraStatus;


// Scene status.
enum { UNLOADED, MUST_BE_LOADED, MUST_BE_REFRESHED, REFRESHED };
// Camera status.
enum { CAMERA_NOTHING, CAMERA_ORBIT, CAMERA_ZOOM, CAMERA_PAN};


// Menu item ids.
#define PRODUCER_PERSPECTIVE_ITEM   100
#define PRODUCER_TOP_ITEM           101
#define PRODUCER_BOTTOM_ITEM        102
#define PRODUCER_FRONT_ITEM         103
#define PRODUCER_BACK_ITEM          104
#define PRODUCER_RIGHT_ITEM         105
#define PRODUCER_LEFT_ITEM          106
#define CAMERA_SWITCHER_ITEM        107
#define PLAY_ANIMATION              200

const int MENU_SHADING_MODE_WIREFRAME = 300;
const int MENU_SHADING_MODE_SHADED = 301;
const char * MENU_STRING_SHADING_MODE_WIREFRAME = "Wireframe";
const char * MENU_STRING_SHADING_MODE_SHADED = "Shaded";

const int MENU_EXIT = 400;

int main(int argc, char** argv)
{
	// Set exit function to destroy objects created by the FBX SDK.
//	atexit(ExitFunction);


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(720, 486); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ViewScene");

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutDisplayFunc(DisplayCallback); 
	glutReshapeFunc(ReshapeCallback);
	glutKeyboardFunc(KeyboardCallback);
	glutMouseFunc(MouseCallback);
	glutMotionFunc(MotionCallback);
    // Initialize the scene status flag.
	gSceneStatus = UNLOADED;
	// Create the FBX SDK manager which is the object allocator for almost 
	// all the classes in the SDK and create the scene.
	InitializeSdkObjects(gSdkManager, gScene);
	gWindowMessage.Reset(new KString());
	gFileName.Reset(new KString());
	*gFileName = argv[1];
	if (gSdkManager)
	{
		// Create the importer.
		int lFileFormat = -1;
		gImporter = KFbxImporter::Create(gSdkManager,"");
		if (!gSdkManager->GetIOPluginRegistry()->DetectReaderFileFormat(*gFileName, lFileFormat) )
		{
			// Unrecognizable file format. Try to fall back to KFbxImporter::eFBX_BINARY
			lFileFormat = gSdkManager->GetIOPluginRegistry()->FindReaderIDByDescription( "FBX binary (*.fbx)" );;
		}
		// Initialize the importer by providing a filename.
		if(gImporter->Initialize(gFileName->Buffer(), lFileFormat) == true)
		{
			// The file is going to be imported at 
			// the end of the first display callback.
			*gWindowMessage = "Importing file ";
			*gWindowMessage += *gFileName;
			*gWindowMessage += "\nPlease wait!";
			// Set scene status flag to ready to load.
			gSceneStatus = MUST_BE_LOADED;
		}
		else
		{
			*gWindowMessage = "Unable to open file ";
			*gWindowMessage += *gFileName;
			*gWindowMessage += "\nError reported: ";
			*gWindowMessage += gImporter->GetLastErrorString();
			*gWindowMessage += "\nEsc to exit";
		}
	}
	else
	{
		*gWindowMessage = "Unable to create the FBX SDK manager";
		*gWindowMessage += "\nEsc to exit";
	}

	// When gPoseIndex is not -1, draw the scene at that pose
	gPoseIndex = -1;
	glutMainLoop();
	return 0;
}
/*
// Function to destroy objects created by the FBX SDK.
void ExitFunction()
{
	// Delete the FBX SDK manager. All the objects that have been allocated 
	// using the FBX SDK manager and that haven't been explicitly destroyed 
	// are automatically destroyed at the same time.
	if (gSdkManager) gSdkManager->Destroy();
	gSdkManager = NULL;

	// Delete the array used to associate menu ids with animation stack names.
	FbxSdkDeleteAndClear(gAnimStackNameArray);

	delete gShadingManager;
}
*/

void ImportFunction() 
{
	if (gSceneStatus == MUST_BE_LOADED)
	{
		if(gImporter->Import(gScene) == true)
		{
			gSceneStatus = MUST_BE_REFRESHED;

			KFbxAxisSystem SceneAxisSystem = gScene->GetGlobalSettings().GetAxisSystem();
			KFbxAxisSystem OurAxisSystem(KFbxAxisSystem::YAxis, KFbxAxisSystem::ParityOdd, KFbxAxisSystem::RightHanded);
			if( SceneAxisSystem != OurAxisSystem )
			{
				OurAxisSystem.ConvertScene(gScene);
			}
			KFbxSystemUnit SceneSystemUnit = gScene->GetGlobalSettings().GetSystemUnit();
			if( SceneSystemUnit.GetScaleFactor() != 1.0 )
			{
				KFbxSystemUnit OurSystemUnit(1.0);
				OurSystemUnit.ConvertScene(gScene);
			}
			ConvertNurbsAndPatch(gSdkManager, gScene);
			PreparePointCacheData(gScene);
			FillCameraArray(gScene, gCameraArray);
			gScene->FillAnimStackNameArray(gAnimStackNameArray);
			FillPoseArray(gScene, gPoseArray);
			gShadingManager = new ShadingManager(KFbxExtractDirectory(gImporter->GetFileName()));
			gShadingManager->Initialize(gScene);
			CreateMenus();
			gPeriod.SetTime(0, 0, 0, 1, 0, gScene->GetGlobalSettings().GetTimeMode());
			glutTimerFunc((unsigned int) gPeriod.GetMilliSeconds(), TimerCallback, 0);  
		}
		else
			gSceneStatus = UNLOADED;
		gImporter->Destroy();
	}
}


void CreateMenus() // init anim
{
	int i;

	// Create the submenu to select the current animation stack.
	int lCurrentAnimStackIndex = 0;

	// Add the animation stack names.
	for (i = 0; i < gAnimStackNameArray.GetCount(); i++)
	{
		// Track the current animation stack index.
		if (gAnimStackNameArray[i]->Compare(KFbxGet<KString>(gScene->ActiveAnimStackName)) == 0)
		{
			lCurrentAnimStackIndex = i;
		}
	}
	AnimStackSelectionCallback(lCurrentAnimStackIndex);
	// Build the main menu.
}

// Select the current animation stack and set the start, stop and current time.
void AnimStackSelectionCallback( int pItem )
{
	int lNbAnimStacks = gAnimStackNameArray.GetCount();
	if (!lNbAnimStacks || pItem >= lNbAnimStacks)
	{
		return;
	}

	// select the base layer from the animation stack
	gCurrentAnimationStack = gScene->FindMember(FBX_TYPE(KFbxAnimStack), gAnimStackNameArray[pItem]->Buffer());
	if (gCurrentAnimationStack == NULL)
	{
		// this is a problem. The anim stack should be found in the scene!
		return;
	}

	// we assume that the first animation layer connected to the animation stack is the base layer
	// (this is the assumption made in the FBXSDK)
	gCurrentAnimationLayer = gCurrentAnimationStack->GetMember(FBX_TYPE(KFbxAnimLayer), 0);
	gScene->GetEvaluator()->SetContext(gCurrentAnimationStack);

	KFbxTakeInfo* lCurrentTakeInfo = gScene->GetTakeInfo(*(gAnimStackNameArray[pItem]));
	if (lCurrentTakeInfo)
	{
		gStart = lCurrentTakeInfo->mLocalTimeSpan.GetStart();
		gStop = lCurrentTakeInfo->mLocalTimeSpan.GetStop();
	}
	else
	{
		// Take the time line value
		KTimeSpan lTimeLineTimeSpan;
		gScene->GetGlobalSettings().GetTimelineDefaultTimeSpan(lTimeLineTimeSpan);

		gStart = lTimeLineTimeSpan.GetStart();
		gStop  = lTimeLineTimeSpan.GetStop();
	}

	gCurrentTime = gStart;

	// Set the scene status flag to refresh 
	// the scene in the next timer callback.
	gSceneStatus = MUST_BE_REFRESHED;
}

// Trigger the display of the current frame.
void TimerCallback(int)//grosso merdo on a dja
{
	// Ask to display the current frame only if necessary.
	if (gSceneStatus == MUST_BE_REFRESHED)
	{
		glutPostRedisplay();
	}

	// Loop in the animation stack.
	if (gStop > gStart)
	{
		// Set the scene status flag to refresh 
		// the scene in the next timer callback.
		gSceneStatus = MUST_BE_REFRESHED;

		gCurrentTime += gPeriod;

		if (gCurrentTime > gStop) 
		{
			gCurrentTime = gStart;
		}
	}
	// Avoid displaying the same frame on 
	// and on if the animation stack has no length.
	else
	{
		// Set the scene status flag to avoid refreshing 
		// the scene in the next timer callback.
		gSceneStatus = REFRESHED;
	}

	// Call the timer to display the next frame.
	glutTimerFunc((unsigned int) gPeriod.GetMilliSeconds(), TimerCallback, 0);
}


// Refresh the appplication window.
void DisplayCallback()//grosso merdo on a dja

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Test if the scene has been loaded yet.
	if (gSceneStatus != UNLOADED && gSceneStatus != MUST_BE_LOADED)
	{
		gShadingManager->InitializeForOneFrame();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// Set the view to the current camera settings.
		SetCamera(gScene, gCurrentTime, gCurrentAnimationLayer, gCameraArray);

		if (gPoseIndex == -1)
		{
			// Draw the scene at the current time.
			DrawScene(gScene, gCurrentTime);
		}
		else
		{
			// Draw the scene in the specified pose
			DrawSceneAtPose(gScene, gCurrentTime, gPoseIndex);
		}

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	// Draw the window message.
//	DrawText(*gWindowMessage);

	glutSwapBuffers();

	// Import the scene if it's ready to load.
	if (gSceneStatus == MUST_BE_LOADED)
	{
		// This function is only called in the first display callback
		// to make sure that the application window is opened and a 
		// status message is displayed before.
		ImportFunction();
	}
}


// Resize the application window.
void ReshapeCallback(int pWidth, int pHeight)//grosso merdo on a dja

{
	glViewport(0, 0, (GLsizei) pWidth, (GLsizei) pHeight); 
}


// Exit the application from the keyboard.
void KeyboardCallback(unsigned char pKey, int, int)//grosso merdo on a dja

{
	// Exit on ESC key.
	if (pKey == 27)
	{
		exit(0);
	}

	// Zoom In on '+' or '=' keypad keys
	if (pKey == 43 || pKey == 61)
	{
		KFbxCamera* lCamera = GetCurrentCamera(gScene);
		if(lCamera)
		{
			//double lOriginalAperture = sqrt(lCamera->GetApertureWidth());
			CameraZoomIn(gScene, 10);
			gSceneStatus = MUST_BE_REFRESHED;
		}
	}

	// Zoom Out on '-' or '_' keypad keys
	if (pKey == 45 || pKey == 95)
	{
		KFbxCamera* lCamera = GetCurrentCamera(gScene);
		if(lCamera)
		{
			//double lOriginalAperture = sqrt(lCamera->GetApertureWidth()); 
			CameraZoomOut(gScene, 10);
			gSceneStatus = MUST_BE_REFRESHED;
		}
	}

	// 'N' enable/disable normal display
	if (pKey == 'N' || pKey == 'n')
	{
		gShadingManager->SetDrawNormal(!gShadingManager->IsDrawNormal());
	}
}

void MouseCallback(int button, int state, int x, int y) {//grosso merdo on a dja

	// Move the camera (orbit, zoom or pan) with the mouse.

	KFbxCamera* lCamera = GetCurrentCamera(gScene);


	if (lCamera)
	{
		gCamPosition = lCamera->Position.Get();
		gCamCenter = lCamera->InterestPosition.Get();
		gRoll = lCamera->Roll.Get();
	}
	gX = x;
	gY = y;

	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			// ORBIT (or PAN)
			switch (state) {
				case GLUT_DOWN:
					if (gCameraStatus == CAMERA_ZOOM) {
						gCameraStatus = CAMERA_PAN;
					} else {
						gCameraStatus = CAMERA_ORBIT;
					}
					break;
				default:
					if (gCameraStatus == CAMERA_PAN) {
						gCameraStatus = CAMERA_ZOOM;
					} else {
						gCameraStatus = CAMERA_NOTHING;
					}
					break;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			// ZOOM (or PAN)
			switch (state) {
				case GLUT_DOWN:
					if (gCameraStatus == CAMERA_ORBIT) {
						gCameraStatus = CAMERA_PAN;
					} else {
						gCameraStatus = CAMERA_ZOOM;
					}
					break;
				default:
					if (gCameraStatus == CAMERA_PAN) {
						gCameraStatus = CAMERA_ORBIT;
					} else {
						gCameraStatus = CAMERA_NOTHING;
					}
					break;
			}
			break;
	}

}

void MotionCallback(int x, int y) {//grosso merdo on a dja


	int motion;

	switch (gCameraStatus) {
		case CAMERA_ORBIT:
			CameraOrbit(gScene, gCamPosition, gRoll, x-gX, gY-y);
			gSceneStatus = MUST_BE_REFRESHED;
			break;
		case CAMERA_ZOOM:
			motion = gY-y;
			if (motion > 0) {
				CameraZoomIn(gScene, motion);
			} else {
				CameraZoomOut(gScene, -motion);
			}
			gY = y;
			gSceneStatus = MUST_BE_REFRESHED;
			break;
		case CAMERA_PAN:
			CameraPan(gScene, gCamPosition, gCamCenter, gRoll, x-gX, gY-y);
			gSceneStatus = MUST_BE_REFRESHED;
			break;
	}

}

