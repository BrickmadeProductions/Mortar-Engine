#include "RenderCommands.h"

//this class creates calls to the virtual renderAPI scope that is defined through window creation
namespace MortarCore
{
    Scope<RenderAPI> RenderCommands::s_RenderAPI = RenderAPI::Create();
}