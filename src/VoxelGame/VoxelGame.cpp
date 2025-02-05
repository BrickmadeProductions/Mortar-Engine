#include "Utils.h"
#include "EntryPoint.h"

class VoxelGame : public MortarCore::Application
{
public:

	VoxelGame(const MortarCore::ApplicationSpecification& specification) : MortarCore::Application(specification)
	{
		

	}
	~VoxelGame() 
	{

	}
};

MortarCore::Application* MortarCore::CreateApplication(MortarCore::ApplicationCommandLineArgs args)
{
	MortarCore::ApplicationSpecification spec = { "Voxel Game",  MortarCore::Renderer::OPENGL, 1920, 1080 };

	return new VoxelGame(spec);
}