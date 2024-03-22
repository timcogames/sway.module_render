#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geombuilder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Geom::Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder)
    : core::foundation::Uniqueable<std::string>(core::misc::newGuid<UUID_NBR_OF_GROUPS>(UUID_MAGIC))
    , gapiPlugin_(plug)
    , builder_(builder)
    , attribLayout_(nullptr) {}

Geom::~Geom() {
  std::fill(buffers_.begin(), buffers_.end(), std::nullopt);
  // SAFE_DELETE_OBJECT(attribLayout_);
}

void Geom::create(const GeometryCreateInfo &info, EffectPtr_t effect,
    std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs) {
  attribLayout_ = gapiPlugin_->createVertexAttribLayout(effect->getShaderProgram());
  for (const auto &attrib : attribs) {
    auto attribDesc = attrib.second->getDescriptor();
    // std::cout << "ATTRIB " << attribDesc.semantic << "(" << std::boolalpha << attribDesc.enabled << ")" << std::endl;
    if (attribDesc.enabled) {
      attribLayout_->addAttribute(attribDesc);
    }
  }

  std::cout << "VBO " << info.bo[0].desc.capacity << " " << info.bo[0].desc.byteStride << std::endl;
  std::cout << "IBO " << info.bo[1].desc.capacity << " " << info.bo[1].desc.byteStride << std::endl;

  auto createBuffers = [&, next = 0](std::optional<gapi::BufferPtr_t> &buf) mutable {
    if (next == Constants::IDX_EBO && !info.indexed) {
      return;
    }

    buf = std::make_optional<gapi::BufferPtr_t>(gapiPlugin_->createBuffer(builder_->getIdGenerator(), info.bo[next]));
    ++next;
  };

  std::for_each(buffers_.begin(), buffers_.end(), createBuffers);
}

void Geom::bind() {
  this->call<gapi::BufferPtr_t>(gapi::Buffer::BindFunctor());
  attribLayout_->enable();
}

void Geom::unbind() {
  attribLayout_->disable();
  this->call<gapi::BufferPtr_t>(gapi::Buffer::UnbindFunctor());
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
