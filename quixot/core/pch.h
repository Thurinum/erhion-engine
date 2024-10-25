#pragma once

#include <string>
#include <expected>
#include <memory>
#include <optional>

#include "logging.h"

namespace Quixot {
	using string = std::string;
	using string_view = std::string_view;

	template<typename T>
	using maybe = std::optional<T>;

	template<typename T, typename E>
	using either = std::expected<T, E>;
	using std::unexpected;

	using std::shared_ptr;
	using std::make_shared;
	using std::unique_ptr;
	using std::make_unique;
	using std::weak_ptr;
}