#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <filesystem>

using namespace geode::prelude;

static std::filesystem::path getPath(char const* key) {
	return Mod::get()->getSettingValue<std::filesystem::path>(key);
}

class $modify(CustomBgMenu, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		auto path = getPath("bg-path");
		if (path.empty() || !std::filesystem::exists(path)) return true;
		auto sprite = CCSprite::create(path.string().c_str());
		if (!sprite) return true;
		auto win = CCDirector::get()->getWinSize();
		sprite->setPosition(win / 2);
		sprite->setScale(std::max(win.width / sprite->getContentWidth(),
		                          win.height / sprite->getContentHeight()));
		sprite->setZOrder(-100);
		this->addChild(sprite);
		if (auto old = this->getChildByID("main-menu-bg")) old->setVisible(false);
		return true;
	}
};

class $modify(CustomMenuMusic, FMODAudioEngine) {
	void playMusic(gd::string path, bool shouldLoop, float fadeInTime, int channel) {
		if (path == "menuLoop.mp3") {
			auto custom = getPath("music-path");
			if (!custom.empty() && std::filesystem::exists(custom)) path = custom.string();
		}
		FMODAudioEngine::playMusic(path, shouldLoop, fadeInTime, channel);
	}
};
