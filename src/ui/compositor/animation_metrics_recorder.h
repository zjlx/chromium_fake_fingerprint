// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_ANIMATION_METRICS_RECORDER_H_
#define UI_COMPOSITOR_ANIMATION_METRICS_RECORDER_H_

#include "base/optional.h"
#include "base/time/time.h"
#include "ui/compositor/compositor_export.h"

namespace ui {

class AnimationMetricsReporter;

class COMPOSITOR_EXPORT AnimationMetricsRecorder {
 public:
  explicit AnimationMetricsRecorder(AnimationMetricsReporter* reporter);
  AnimationMetricsRecorder(const AnimationMetricsRecorder&) = delete;
  AnimationMetricsRecorder& operator=(const AnimationMetricsRecorder&) = delete;
  ~AnimationMetricsRecorder();

  // Called when the animator is attached to/detached from a Compositor to
  // update |start_frame_number_|.
  void OnAnimatorAttached(base::Optional<int> frame_number);
  void OnAnimatorDetached();

  void OnAnimationStart(base::Optional<int> start_frame_number,
                        base::TimeTicks effective_start_time,
                        base::TimeDelta duration);
  void OnAnimationEnd(base::Optional<int> end_frame_number, float refresh_rate);

 private:
  AnimationMetricsReporter* const reporter_;

  // Variables set at the start of an animation which are required to compute
  // the smoothness when the animation ends.
  // |start_frame_number_| is the frame number in relevant Compositor when
  // the animation starts. If not set, it means the animator and its Layer
  // is not attached to a Compositor when the animation starts, or is
  // detached from the Compositor partway through the animation.
  base::Optional<int> start_frame_number_;
  base::TimeTicks effective_start_time_;
  base::TimeDelta duration_;

  // Whether animator is detached from Compositor partway through the animation.
  // If it is true, no metrics is reported because the number of frames could
  // not be counted correctly in such case.
  bool animator_detached_after_start_ = false;
};

}  // namespace ui

#endif  // UI_COMPOSITOR_ANIMATION_METRICS_RECORDER_H_
