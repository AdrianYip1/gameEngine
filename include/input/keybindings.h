#pragma once
#include <unordered_map>
#include <input/input.h>

template<class Action>
struct Keybindings {
	std::unordered_map<Action, int> map;

	void bind(Action a, int key) { map[a] = key; }
	int keyFor(Action a) const {
		auto it = map.find(a);
		return it == map.end() ? -1 : it->second;
	}
	bool isActionDown(const Input& in, Action a) const {
		int key = keyFor(a);
		return key >= 0 && in.isKeyDown(key);
	}
};