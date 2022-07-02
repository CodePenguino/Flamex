#include "core/window.hpp"
#include "core/input.hpp"
#include "core/time.hpp"
#include "rendering/shader.hpp"
#include "rendering/renderer.hpp"
#include "ecs/scene.hpp"

using namespace ECS;
using namespace Math;

static Scene scene;
static Shader sprite_shader;
static Entity sprite1;
static Entity sprite2;
static Entity camera;

// Update inputs
void processInputs()
{
	Transform3DComponent& sprite2_transform = sprite2.get_component<Transform3DComponent>();
	Transform3DComponent& sprite1_transform = sprite1.get_component<Transform3DComponent>();

	const float move_speed = Time::delta;

	// Translation
	Input::axis(sprite2_transform.position.x, move_speed, GLFW_KEY_D, GLFW_KEY_A);
	Input::axis(sprite2_transform.position.y, move_speed, GLFW_KEY_W, GLFW_KEY_S);
	Input::axis(sprite2_transform.position.z, move_speed, GLFW_KEY_Q, GLFW_KEY_E);

	// Point arrow
	sprite1_transform.lookAt(sprite2_transform.position);
	sprite1_transform.rotation *= euler(Vector3f(-90,0,0));
}

// Update and draw
void update()
{
	Time::update();
	Input::update_joysticks();

	window.set_background_color(0.0f, 0.5f, 0.5f);

	Renderer2D::use_shader(sprite_shader);
	camera.get_component<CameraComponent>().update_perspective();

	Renderer2D::draw(sprite2);
	Renderer2D::draw(sprite1);
}

int main()
{
	// Basic initialization
	window.create(1280, 720, "Flamex");
	window.set_icon("../../res/images/icon.bmp");
	window.set_callbacks(processInputs, update);
	Time::init();
	scene.use();

	sprite_shader.create("../../res/shaders/shader.vs", "../../res/shaders/shader.fs");
	sprite1.init_sprite("../../res/images/Arrow.png");
	sprite2.init_sprite("../../res/images/Placeholder.png");

	// Set up sprite transforms
	sprite1.get_component<Transform3DComponent>().scale = Vector3f(5.0f);
	sprite2.get_component<Transform3DComponent>() = { Vector3f(0.85f, -0.6f, 0.5f), Quaternion(), Vector3f(0.7f) };

	camera.init_camera_perspective(Vector3f(0,0,-3));
	Renderer2D::use_camera(camera);

	// Run the loop
	window.loop();

	return 0;
}