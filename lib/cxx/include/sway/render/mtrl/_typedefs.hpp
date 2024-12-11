#ifndef SWAY_RENDER_MTRL_TYPEDEFS_HPP
#define SWAY_RENDER_MTRL_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

namespace ShaderTypedefs {
// using SourcePair_t = std::unordered_map<gapi::ShaderType::Enum, std::string>;
using SourcePair_t = std::array<std::string, 2>;
using NamePair_t = std::array<std::string, 2>;
}  // namespace ShaderTypedefs

class Material;
namespace MaterialTypedefs {
using Ptr_t = Material *;
using SharedPtr_t = std::shared_ptr<Material>;
using UniquePtr_t = std::unique_ptr<Material>;
using Container_t = std::map<std::string, SharedPtr_t>;
}  // namespace MaterialTypedefs

class MaterialManager;
namespace MaterialManagerTypedefs {
using SharedPtr_t = std::shared_ptr<MaterialManager>;
}  // namespace MaterialManagerTypedefs

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_MTRL_TYPEDEFS_HPP
