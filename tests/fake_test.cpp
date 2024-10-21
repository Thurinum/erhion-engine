#include <gtest/gtest.h>
#include "renderer/shader.h"

using namespace Erhion::Engine;

TEST(FakeTest, DummyTest) {
	Shader s("", Vertex);

	ASSERT_TRUE(true);
}
