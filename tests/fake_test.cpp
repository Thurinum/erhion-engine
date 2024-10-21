#include <gtest/gtest.h>
#include "renderer/shader.h"

using namespace Quixot::Renderer;

TEST(FakeTest, DummyTest) {
	Shader s("", Vertex);

	ASSERT_TRUE(true);
}
