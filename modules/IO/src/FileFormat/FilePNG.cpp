// ----------------------------------------------------------------------------
// -                        Open3D: www.open-3d.org                            -
// ----------------------------------------------------------------------------
// Imported on Apr 11th, 2018 from the Open3D project
// Copyright (c) 2018 www.open3d.org
// released under MIT licence
//
// A fork of their project is avilable at legacy-code.open-3d.org
// Refer to http://legacy-code.open-3d.org/blob/master/LICENSE
// for their full licence
// Check http://legacy-code.open-3d.org/graphs/contributors
// to get the list of their contributors and their contributions
//
// The rights of any later updates or modifications are reserved
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018, Hamdi Sahloul - www.open-3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <Open3D/IO/ClassIO/ImageIO.h>

#include <png.h>
#include <Open3D/Core/Utility/Console.h>

namespace open3d {

namespace {

void SetPNGImageFromImage(const Image &image, png_image &pngimage)
{
    pngimage.width = image.width_;
    pngimage.height = image.height_;
    pngimage.format = 0;
    if (image.bytes_per_channel_ == 2) {
        pngimage.format |= PNG_FORMAT_FLAG_LINEAR;
    }
    if (image.num_of_channels_ == 3) {
        pngimage.format |= PNG_FORMAT_FLAG_COLOR;
    }
}

}   // unnamed namespace

bool ReadImageFromPNG(const std::string &filename, Image &image)
{
    png_image pngimage;
    memset(&pngimage, 0, sizeof(pngimage));
    pngimage.version = PNG_IMAGE_VERSION;
    if (png_image_begin_read_from_file(&pngimage, filename.c_str()) == 0) {
        PrintWarning("Read PNG failed: unable to parse header.\n");
        return false;
    }

    // We only support two channel types: gray, and RGB.
    // There is no alpha channel.
    // bytes_per_channel is determined by PNG_FORMAT_FLAG_LINEAR flag.
    image.PrepareImage(pngimage.width, pngimage.height,
            (pngimage.format & PNG_FORMAT_FLAG_COLOR) ? 3 : 1,
            (pngimage.format & PNG_FORMAT_FLAG_LINEAR) ? 2 : 1);
    SetPNGImageFromImage(image, pngimage);
    if (png_image_finish_read(&pngimage, NULL, image.data_.data(),
            0, NULL) == 0) {
        PrintWarning("Read PNG failed: unable to read file: %s\n", filename.c_str());
        return false;
    }
    return true;
}

bool WriteImageToPNG(const std::string &filename, const Image &image,
        int quality)
{
    if (image.HasData() == false) {
        PrintWarning("Write PNG failed: image has no data.\n");
        return false;
    }
    png_image pngimage;
    memset(&pngimage, 0, sizeof(pngimage));
    pngimage.version = PNG_IMAGE_VERSION;
    SetPNGImageFromImage(image, pngimage);
    if (png_image_write_to_file(&pngimage, filename.c_str(), 0,
            image.data_.data(), 0, NULL) == 0) {
        PrintWarning("Write PNG failed: unable to write file: %s\n", filename.c_str());
        return false;
    }
    return true;
}

}   // namespace open3d
