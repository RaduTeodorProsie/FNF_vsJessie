#ifndef LANE_H
#define LANE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include <map>
#include <variant>

#include "notes.h"
#include "spriteData.h"

class bLane {
public:
    virtual ~bLane() = default;
    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual void update(const sf::Time &dt) = 0;
    virtual void press() = 0;
    virtual void release() = 0;
    virtual void addLaneSimpleNote(float yPosition = -100.f) = 0;
};

template<tagType LaneSimpleNoteTag_T>
class lane : public bLane{
public:
    using ThisLaneSimpleNoteType = simpleNote<LaneSimpleNoteTag_T>;
    using GameNoteVariant = std::variant<
        ThisLaneSimpleNoteType,
        poisonNote
    >;

    std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> &getSpriteData() {
        return xmlInfo;
    }

private:
    std::deque<GameNoteVariant> currentNotes;
    std::deque<GameNoteVariant> animationNotes;

    std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> xmlInfo;

    std::string name;
    Judge judge;

    const sf::Texture& textureAtlas;

    const double pxPerMsec;
    const std::vector<int> cat = {14, 30, 60, 120};
public:
    // Constructor
    lane(const std::string &lane_name,
         int X,
         const sf::Texture& atlas,
         const sf::IntRect& judgeDefaultRect,
         const sf::IntRect& noteDefaultRect,
         double pixels_per_ms = 1.5,
         int judge_ms_per_frame = 150)
        : name(lane_name),
          judge(atlas, nonStaticStorage({{"default", {judgeDefaultRect}}}), judge_ms_per_frame),
          textureAtlas(atlas),
          pxPerMsec(pixels_per_ms)
    {
        judge.setPosition({static_cast<float>(X), 850});
        // Set default animation for simpleNote static storage
        staticStorage<LaneSimpleNoteTag_T>::set({{"default", {noteDefaultRect}}});
    }

    void draw(sf::RenderTarget& target) const override {
        for (const auto &note: currentNotes) std::visit([&target](auto&& n){ target.draw(n); }, note);
        for (const auto &note: animationNotes) std::visit([&target](auto&& n){ target.draw(n); }, note);
        target.draw(judge);
    }

    double whenNext() const {
        if (currentNotes.empty()) return 0.0;
        return (judge.getPosition().y - std::visit([](auto&& n){ return n.getPosition().y; }, currentNotes.front())) / pxPerMsec;
    }

    void update(const sf::Time &dt) override {
        while (!animationNotes.empty() && std::visit([](auto&& n){ return n.updateAnimation(); }, animationNotes.front()))
            animationNotes.pop_front();
        for (auto &note: animationNotes) {
            std::visit([&](auto& n){ n.updateAnimation(); n.move({0, static_cast<float>(dt.asMilliseconds() * pxPerMsec)}); }, note);
        }
        while (!currentNotes.empty() && std::visit([](auto&& n){ return n.getPosition().y > 1080; }, currentNotes.front())) {
            currentNotes.pop_front();
        }
        for (auto &note: currentNotes) {
            std::visit([&](auto& n){ n.updateAnimation(); n.move({0, static_cast<float>(dt.asMilliseconds() * pxPerMsec)}); }, note);
        }
    }

    void press() override {
        judge.setAnimation("press");
        if (!currentNotes.empty()) {
            if (abs(whenNext()) <= cat.back()) {
                std::visit([](auto& n){ n.hit(); }, currentNotes.front());
                animationNotes.push_back(std::move(currentNotes.front()));
                currentNotes.pop_front();
            }
        }
    }

    void release() override {
        judge.setAnimation("default");
    }

    void addLaneSimpleNote(float yPosition = -100.f) override {
        ThisLaneSimpleNoteType note(textureAtlas);
        note.setPosition({0, yPosition});
        currentNotes.emplace_back(std::move(note));
    }
    void addPoisonNoteToLane(float yPosition = -100.f) {
        poisonNote note(textureAtlas);
        note.setPosition({0, yPosition});
        currentNotes.emplace_back(std::move(note));
    }

    Judge& getJudge() { return judge; }
};

#endif // LANE_H
