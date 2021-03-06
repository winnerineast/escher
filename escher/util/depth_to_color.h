// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "escher/forward_declarations.h"
#include "escher/impl/compute_shader.h"
#include "escher/renderer/timestamper.h"

namespace escher {

// Utility that uses a compute shader to transform a depth image to a color
// image.  One common use-case is for debugging, since Vulkan does not support
// directly bliting a depth image into a color image.
class DepthToColor {
 public:
  DepthToColor(impl::GlslToSpirvCompiler* compiler,
               impl::ImageCache* image_cache,
               ResourceRecycler* resource_recycler);

  TexturePtr Convert(impl::CommandBuffer* command_buffer,
                     const TexturePtr& depth_texture,
                     vk::ImageUsageFlags image_flags,
                     Timestamper* timestamper);

 private:
  impl::GlslToSpirvCompiler* compiler_;
  impl::ImageCache* const image_cache_;
  ResourceRecycler* const resource_recycler_;
  std::unique_ptr<impl::ComputeShader> kernel_;

  FTL_DISALLOW_COPY_AND_ASSIGN(DepthToColor);
};

}  // namespace escher
