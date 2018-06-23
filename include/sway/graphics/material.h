#ifndef SWAY_GRAPHICS_MATERIAL_H
#define SWAY_GRAPHICS_MATERIAL_H

#include <sway/graphics/prereqs.h>
#include <sway/graphics/materialinitialinfo.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Material {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] info
	 *    Первоначальная информация о материале.
	 */
	Material(const MaterialInitialInfo & info);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~Material();

	/*!
	 * \brief
	 *    Привязывает.
	 */
	void bind();

	/*!
	 * \brief
	 *    Отвязывает.
	 */
	void unbind();

	gapi::ShaderProgram * getShaderProgram();

private:
	gapi::ShaderProgram * _shaderProgram; /*!< Указатель на шейдерную программу. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_MATERIAL_H