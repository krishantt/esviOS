/*
 * Copyright (c) 2024, Nico Weber <thakis@chromium.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGfx/ImageFormats/ImageDecoder.h>

namespace Gfx {

namespace JPEG2000 {

enum class SubBand {
    HorizontalLowpassVerticalLowpass,   // "LL" in spec
    HorizontalHighpassVerticalLowpass,  // "HL" in spec
    HorizontalLowpassVerticalHighpass,  // "LH" in spec
    HorizontalHighpassVerticalHighpass, // "HH" in spec
};

}

struct JPEG2000LoadingContext;

class JPEG2000ImageDecoderPlugin : public ImageDecoderPlugin {
public:
    static bool sniff(ReadonlyBytes);
    static ErrorOr<NonnullOwnPtr<ImageDecoderPlugin>> create(ReadonlyBytes);

    virtual ~JPEG2000ImageDecoderPlugin() override;

    virtual IntSize size() override;

    virtual ErrorOr<ImageFrameDescriptor> frame(size_t index, Optional<IntSize> ideal_size = {}) override;

    virtual ErrorOr<Optional<ReadonlyBytes>> icc_data() override;

    virtual NaturalFrameFormat natural_frame_format() const override;
    virtual ErrorOr<NonnullRefPtr<CMYKBitmap>> cmyk_frame() override;

private:
    JPEG2000ImageDecoderPlugin();

    OwnPtr<JPEG2000LoadingContext> m_context;
};

}
