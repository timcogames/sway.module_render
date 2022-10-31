#include <sway/graphics/drawable.hpp>
#include <sway/graphics/material.hpp>
#include <sway/graphics/rendersubqueue.hpp>
#include <sway/graphics/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup_t group)
    : group_(group) {
  drawCall_ = global::getGapiFunctionSet()->createDrawCall();
}

RenderSubqueue::~RenderSubqueue() {
  // Empty
}

void RenderSubqueue::addDrawable(DrawableRef_t drawable) { drawables_.push_back(drawable); }

void RenderSubqueue::render() {
  gapi::BufferSet bufset = {nullptr, nullptr};

  for (const DrawableRef_t &drawable : drawables_) {
    bufset.vbo = drawable->getVBO();
    bufset.ibo = drawable->getIBO();

    drawable->getMaterial()->bind();

    bufset.vbo->bind();
    drawable->getVertexLayout()->enable();

    if (drawCall_) {
      drawCall_->execute(gapi::TopologyType_t::kTriangleList, bufset, core::detail::DataType_t::kUInt);
    }

    drawable->getVertexLayout()->disable();
    bufset.vbo->unbind();

    drawable->getMaterial()->unbind();
  }
}

void RenderSubqueue::setGroup(RenderSubqueueGroup_t group) { group_ = group; }

RenderSubqueueGroup_t RenderSubqueue::getGroup() const { return group_; }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
