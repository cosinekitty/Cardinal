#include <context.hpp>
#include <window/Window.hpp>
#include <patch.hpp>
#include <engine/Engine.hpp>
#include <app/Scene.hpp>
#include <history.hpp>
#include <settings.hpp>

#include "DistrhoPluginUtils.hpp"


namespace rack {


Context::~Context() {
	// Deleting NULL is safe in C++.

	// Set pointers to NULL so other objects will segfault when attempting to access them

	delete window;
	window = NULL;

	delete patch;
	patch = NULL;

	delete scene;
	scene = NULL;

	delete event;
	event = NULL;

	delete history;
	history = NULL;

	delete engine;
	engine = NULL;
}


static thread_local Context* threadContext = nullptr;

Context* contextGet() {
	DISTRHO_SAFE_ASSERT(threadContext != nullptr);
	return threadContext;
}

// Apple's clang incorrectly compiles this function when -O2 or higher is enabled.
#ifdef ARCH_MAC
__attribute__((optnone))
#endif
void contextSet(Context* const context) {
	// DISTRHO_SAFE_ASSERT(threadContext == nullptr);
	threadContext = context;
}


} // namespace rack