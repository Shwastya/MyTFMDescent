#include "engine/system/render.hpp"




int main(int, char*[]) {

	constexpr uint32_t width { 1920 }, height { 1080 };

	const TFM_ECS::RenderSystem_t My_ECS_TFM_Descent { width, height, "MyTFMDescent" };

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

	My_ECS_TFM_Descent.update();

	return 0;

}