// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include <common/data/BatteryUtils.hpp>
#include <common/widgets/BellBattery.hpp>
#include <Image.hpp>

namespace
{
    constexpr auto entries = std::array<battery_utils::BatteryLevelEntry, 6>{{{{0, 9}, "bell_battery_empty"},
                                                                              {{10, 19}, "bell_battery_lvl1"},
                                                                              {{20, 39}, "bell_battery_lvl2"},
                                                                              {{40, 69}, "bell_battery_lvl3"},
                                                                              {{70, 95}, "bell_battery_lvl4"},
                                                                              {{96, 100}, "bell_battery_lvl5"}}};

    constexpr auto betteryFullLevel = 100;
    constexpr auto lowBatteryLimit  = 20;
    constexpr auto singleDigitLimit = 10;
} // namespace

namespace gui
{
    BellBattery::BellBattery(Item *parent, uint32_t x, uint32_t y, uint32_t w, uint32_t h) : HBox(parent, x, y, w, h)
    {
        img = new Image(this, battery::battery_low, gui::ImageTypeSpecifier::W_M);
        img->setAlignment(Alignment(Alignment::Horizontal::Left, Alignment::Vertical::Center));
        img->setMargins(gui::Margins(0, 0, battery::image_right_margin, 0));

        percentText = new TextFixedSize(this, 0, 0, 0, 0);
        percentText->setMinimumSize(battery::percent_w, battery::percent_h);
        percentText->setFont(battery::font_small);
        percentText->setAlignment(Alignment(Alignment::Horizontal::Left, Alignment::Vertical::Center));
        percentText->setEdges(RectangleEdge::None);
        percentText->activeItem = false;
        percentText->drawUnderline(false);
    }

    void BellBattery::update(const Store::Battery &batteryContext)
    {
        const auto image = battery_utils::getBatteryLevelImage(entries, batteryContext.level);
        if (not image) {
            return;
        }

        const auto level = batteryContext.level;

        if (batteryContext.state == Store::Battery::State::Charging) {
            img->set(battery::battery_charging, gui::ImageTypeSpecifier::W_M);

            if (level == betteryFullLevel) {
                img->setMargins(gui::Margins(0, 0, battery::image_right_margin, 0));
                img->informContentChanged();
            }
            else if (level < singleDigitLimit) {
                img->setMargins(gui::Margins(battery::image_left_margin_big, 0, battery::image_right_margin, 0));
                img->informContentChanged();
            }
            else {
                img->setMargins(gui::Margins(battery::image_left_margin, 0, battery::image_right_margin, 0));
                img->informContentChanged();
            }
        }
        else {
            if (level <= lowBatteryLimit) {
                if (level < singleDigitLimit) {
                    img->setMargins(gui::Margins(battery::image_left_margin_big, 0, battery::image_right_margin, 0));
                }
                else {
                    img->setMargins(gui::Margins(battery::image_left_margin, 0, battery::image_right_margin, 0));
                }
            }
            img->set(image->data(), gui::ImageTypeSpecifier::W_M);
            img->informContentChanged();
        }

        if (batteryPercentMode == BatteryPercentMode::Static || level < lowBatteryLimit ||
            batteryContext.state == Store::Battery::State::Charging) {
            percentText->setText(std::to_string(level) + "%");
            percentText->setVisible(true);
        }
        else {
            percentText->setVisible(false);
        }
        percentText->informContentChanged();
    }

    void BellBattery::setBatteryPercentMode(BatteryPercentMode mode)
    {
        batteryPercentMode = mode;
    }

    std::uint32_t BellBattery::getLevel()
    {
        auto percentTextStr  = std::string(percentText->getText().c_str());
        auto batteryLevelStr = percentTextStr.substr(0, percentTextStr.size() - 1);
        return std::stoi(batteryLevelStr);
    }
} // namespace gui