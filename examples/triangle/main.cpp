#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/canvas.h>
#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi.h>
#include <sway/graphics.h>

#include <memory> // std::shared_ptr, std::make_shared

using namespace sway;

class RenderSubsystemContext : public core::foundation::Context {
public:
	RenderSubsystemContext() {
		_subsystem = std::make_shared<graphics::RenderSubsystem>(this);

		gapi::ShaderCreateInfoSet shaderCreateInfoSet;
		shaderCreateInfoSet.vs.type = gapi::ShaderType_t::kVertex;
		shaderCreateInfoSet.vs.code = 
			"attribute vec3 attr_position;" \
			"void main() {" \
			"	gl_Position = vec4(attr_position, 1.0);" \
			"}";
		shaderCreateInfoSet.fs.type = gapi::ShaderType_t::kFragment;
		shaderCreateInfoSet.fs.code = 
			"void main() {" \
			"	gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);" \
			"}";
		auto material = std::make_shared<graphics::Material>(shaderCreateInfoSet);

		auto data = std::make_shared<graphics::VertexData>(3);
		auto channel = data->createChannel<math::vec3f_t>(gapi::VertexSemantic_t::kPosition);

		auto o = math::vec3f_t(-0.5f,-0.5f, 0.0f);
		channel->addAnyData(o.data());
		auto t = math::vec3f_t( 0.5f,-0.5f, 0.0f);
		channel->addAnyData(t.data());
		auto f = math::vec3f_t( 0.0f, 0.5f, 0.0f);
		channel->addAnyData(f.data());

		gapi::BufferCreateInfoSet bufferCreateInfoSet;
		bufferCreateInfoSet.vb.desc.target = gapi::BufferTarget_t::kArray;
		bufferCreateInfoSet.vb.desc.usage = gapi::BufferUsage_t::kStatic;
		bufferCreateInfoSet.vb.desc.byteStride = sizeof(math::VertexPosition);
		bufferCreateInfoSet.vb.desc.capacity = data->getVertexCount();
		bufferCreateInfoSet.vb.data = (void *)data->getRaw();

		auto subqueue = std::make_shared<graphics::RenderSubqueue>();
		auto staticMesh = std::make_shared<graphics::StaticMesh>(subqueue, material, data, bufferCreateInfoSet);
		auto queue = _subsystem->createQueue();
		queue->setPriority(core::intrusive::kPriority_High);
		queue->addSubqueue(subqueue);
	}

	virtual ~RenderSubsystemContext() {
		// Empty
	}

	void drawFrame() {
		_subsystem->render();
	}

private:
	std::shared_ptr<graphics::RenderSubsystem> _subsystem;
};

int main(int argc, char * argv[]) {
	glx11::WindowInitialInfo windowInitialInfo;
	windowInitialInfo.title = "examples";
	windowInitialInfo.size.normal = math::size2i_t(800, 600);
	windowInitialInfo.fullscreen = false;
	windowInitialInfo.resizable = false;

	auto connection = std::make_shared<glx11::XScreenConnection>();
	auto canvas = std::make_shared<glx11::Canvas>(connection, windowInitialInfo);

	canvas->show();
	canvas->getContext()->makeCurrent();

	auto rendersystemContext = std::make_shared<RenderSubsystemContext>();

	while (canvas->eventLoop(true)) {
		canvas->getContext()->makeCurrent();

		rendersystemContext->drawFrame();

		canvas->getContext()->present();
		canvas->getContext()->doneCurrent();
	}

	return 0;
}
