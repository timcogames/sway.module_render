#ifndef SWAY_GRAPHICS_MATERIALMANAGER_HPP
#define SWAY_GRAPHICS_MATERIALMANAGER_HPP

#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class MaterialManager {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  MaterialManager();

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  ~MaterialManager();

  void createMaterial(const std::string &name);

  // void read(const boost::property_tree::ptree &pt);
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_MATERIALMANAGER_HPP
