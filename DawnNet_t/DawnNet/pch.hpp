#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <functional>

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/bind.hpp>

#include <DawnNet/Core/Types.hpp>
#include <DawnNet/Core/TLS.hpp>
#include <DawnNet/Core/Macro.hpp>

#include <DawnNet/Lock/Lock.hpp>
#include <DawnNet/Buffer/SendBuffer.hpp>
