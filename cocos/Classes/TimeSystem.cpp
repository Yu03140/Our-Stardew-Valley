#include "TimeSystem.h"

USING_NS_CC;

TimeSystem* TimeSystem::instance = nullptr;

TimeSystem::TimeSystem() {
    year = 2024;              
    day = 1;                 
    hour = 0;                  
    season = 1;               
    droughtDay = false;      

    timeLabel = Label::createWithSystemFont("", "Arial", 30);
    droughtLabel = Label::createWithSystemFont("", "Arial", 30);

    timeLabel->setPosition(Vec2(2400, 1450));  
    droughtLabel->setPosition(Vec2(2400, 1380)); 

    timeLabel->setMaxLineWidth(500);  
    droughtLabel->setMaxLineWidth(500); 

    timeLabel->setTextColor(Color4B::BLACK);
    droughtLabel->setTextColor(Color4B::BLACK);


    this->addChild(timeLabel, 2);  
    this->addChild(droughtLabel, 2);

    Node::onEnter();
    schedule([this](float deltaTime) {
        log("Updating TimeSystem...");
        update(deltaTime);
        }, 10.0f, "update_key");  
    this->scheduleUpdate();



}

TimeSystem::~TimeSystem() {
}

TimeSystem* TimeSystem::getInstance() {
    if (instance == nullptr) {
        instance = new TimeSystem();
    }

    auto currentScene = Director::getInstance()->getRunningScene();
    if (instance->getParent() != currentScene) {
        currentScene->addChild(instance);
    }

    return instance;
}


void TimeSystem::update(float deltaTime) {
    log("Entering update method");

    hour += (deltaTime * TIME_SCALE);

    if (hour >= 24) {
        hour -= 24;  
        changeDay(); 
    }

  
    updateDisplay();

}

void TimeSystem::changeDay() {
    day++;  
    randomDroughtDay(); 

    if (day > MAX_DAYS_IN_MONTH) {
        day = 1;
        changeSeason();
    }
}

void TimeSystem::changeSeason() {
    season++;
    if (season > SEASON_COUNT) { 
        season = 1;
        changeYear();
    }
}

void TimeSystem::changeYear() {
    year++;  
}

void TimeSystem::randomDroughtDay() {
    if ((rand() % 100) < (DROUGHT_DAY_PROBABILITY * 100)) {
        droughtDay = true;  
    }
    else {
        droughtDay = false;  
    }
}

void TimeSystem::updateDisplay() {

    std::string timeText = "Year: " + std::to_string(year) + "\n";
    timeText += "Season: " + std::to_string(season) + "\n";
    timeText += "Day: " + std::to_string(day) + "\n";
    timeText += "Hour: " + std::to_string(hour) + "\n";

    timeLabel->setString(timeText);

    std::string droughtText = "Drought Day: " + std::string(droughtDay ? "Yes" : "No");
    log("TimeLabel Updated: %s", timeText.c_str()); 
    droughtLabel->setString(droughtText);

    log("TimeLabel Position: x = %f, y = %f", timeLabel->getPositionX(), timeLabel->getPositionY());
}
