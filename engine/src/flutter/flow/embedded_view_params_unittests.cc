// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/flow/embedded_views.h"
#include "flutter/fml/logging.h"
#include "gtest/gtest.h"

namespace flutter {
namespace testing {

TEST(EmbeddedViewParams, GetBoundingRectAfterMutationsWithNoMutations) {
  MutatorsStack stack;
  SkMatrix matrix;

  EmbeddedViewParams params(matrix, SkSize::Make(1, 1), stack);
  const SkRect& rect = params.finalBoundingRect();
  ASSERT_TRUE(SkScalarNearlyEqual(rect.x(), 0));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.y(), 0));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.width(), 1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.height(), 1));
}

TEST(EmbeddedViewParams, GetBoundingRectAfterMutationsWithScale) {
  MutatorsStack stack;
  DlMatrix matrix = DlMatrix::MakeScale({2, 2, 1});
  stack.PushTransform(matrix);

  EmbeddedViewParams params(ToSkMatrix(matrix), SkSize::Make(1, 1), stack);
  const SkRect& rect = params.finalBoundingRect();
  ASSERT_TRUE(SkScalarNearlyEqual(rect.x(), 0));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.y(), 0));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.width(), 2));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.height(), 2));
}

TEST(EmbeddedViewParams, GetBoundingRectAfterMutationsWithTranslate) {
  MutatorsStack stack;
  DlMatrix matrix = DlMatrix::MakeTranslation({1, 1});
  stack.PushTransform(matrix);

  EmbeddedViewParams params(ToSkMatrix(matrix), SkSize::Make(1, 1), stack);
  const SkRect& rect = params.finalBoundingRect();
  ASSERT_TRUE(SkScalarNearlyEqual(rect.x(), 1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.y(), 1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.width(), 1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.height(), 1));
}

TEST(EmbeddedViewParams, GetBoundingRectAfterMutationsWithRotation90) {
  MutatorsStack stack;
  DlMatrix matrix = DlMatrix::MakeRotationZ(DlDegrees(90));
  stack.PushTransform(matrix);

  EmbeddedViewParams params(ToSkMatrix(matrix), SkSize::Make(1, 1), stack);
  const SkRect& rect = params.finalBoundingRect();

  ASSERT_TRUE(SkScalarNearlyEqual(rect.x(), -1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.y(), 0));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.width(), 1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.height(), 1));
}

TEST(EmbeddedViewParams, GetBoundingRectAfterMutationsWithRotation45) {
  MutatorsStack stack;
  DlMatrix matrix = DlMatrix::MakeRotationZ(DlDegrees(45));
  stack.PushTransform(matrix);

  EmbeddedViewParams params(ToSkMatrix(matrix), SkSize::Make(1, 1), stack);
  const SkRect& rect = params.finalBoundingRect();
  ASSERT_TRUE(SkScalarNearlyEqual(rect.x(), -sqrt(2) / 2));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.y(), 0));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.width(), sqrt(2)));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.height(), sqrt(2)));
}

TEST(EmbeddedViewParams,
     GetBoundingRectAfterMutationsWithTranslateScaleAndRotation) {
  DlMatrix matrix = DlMatrix::MakeTranslation({2, 2}) *
                    DlMatrix::MakeScale({3, 3, 1}) *
                    DlMatrix::MakeRotationZ(DlDegrees(90));

  MutatorsStack stack;
  stack.PushTransform(matrix);

  EmbeddedViewParams params(ToSkMatrix(matrix), SkSize::Make(1, 1), stack);
  const SkRect& rect = params.finalBoundingRect();
  ASSERT_TRUE(SkScalarNearlyEqual(rect.x(), -1));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.y(), 2));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.width(), 3));
  ASSERT_TRUE(SkScalarNearlyEqual(rect.height(), 3));
}

}  // namespace testing
}  // namespace flutter
