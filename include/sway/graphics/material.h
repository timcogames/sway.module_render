#ifndef SWAY_GRAPHICS_MATERIAL_H
#define SWAY_GRAPHICS_MATERIAL_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Material {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] infoSet
	 *    Первоначальная информация о материале.
	 */
	Material(const gapi::ShaderCreateInfoSet & infoSet);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *    Освобождает захваченные ресурсы.
	 */
	~Material();

	void loadFromXml();

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

	gapi::ShaderProgramRef_t getShaderProgram();

private:
	gapi::ShaderProgramRef_t _shaderProgram; /*!< Указатель на шейдерную программу. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_MATERIAL_H
