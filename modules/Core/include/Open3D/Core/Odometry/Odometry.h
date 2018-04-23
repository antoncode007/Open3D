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

#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <Eigen/Core>
#include <Open3D/Core/Utility/Console.h>
#include <Open3D/Core/Odometry/OdometryOption.h>
#include <Open3D/Core/Odometry/RGBDOdometryJacobian.h>
#include <Open3D/Core/Camera/PinholeCameraIntrinsic.h>
#include <Open3D/Core/Utility/Eigen.h>

namespace open3d {

class RGBDImage;

/// Function to estimate 6D odometry between two RGB-D images
/// output: is_success, 4x4 motion matrix, 6x6 information matrix
std::tuple<bool, Eigen::Matrix4d, Eigen::Matrix6d>
        ComputeRGBDOdometry(const RGBDImage &source, const RGBDImage &target,
        const PinholeCameraIntrinsic &pinhole_camera_intrinsic =
        PinholeCameraIntrinsic(),
        const Eigen::Matrix4d &odo_init = Eigen::Matrix4d::Identity(),
        const RGBDOdometryJacobian &jacobian_method =
        RGBDOdometryJacobianFromHybridTerm(),
        const OdometryOption &option = OdometryOption());

}   // namespace open3d
