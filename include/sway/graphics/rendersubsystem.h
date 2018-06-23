#ifndef SWAY_GRAPHICS_RENDERSUBSYSTEM_H
#define SWAY_GRAPHICS_RENDERSUBSYSTEM_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubsystem : public core::foundation::Object {
	DECLARE_OBJECT(RenderSubsystem, core::foundation::Object)

public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] context
	 *    Контекст подсистемы.
	 */
	RenderSubsystem(core::foundation::Context * context);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~RenderSubsystem();

private:
	gapi::Capabilities * _caps;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBSYSTEM_H
