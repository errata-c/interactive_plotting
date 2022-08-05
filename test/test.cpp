#include <iplot/Context.hpp>
#include <memory>

int main() {
	std::unique_ptr<iplot::Context> ctx(new iplot::Context(1000, 600));
	return ctx->run();
}