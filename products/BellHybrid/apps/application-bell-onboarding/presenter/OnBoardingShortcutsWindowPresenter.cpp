// Copyright (c) 2017-2022, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include "OnBoardingShortcutsWindowPresenter.hpp"
#include "layouts/OnBoardingShortcutsLayoutProvider.hpp"

namespace app::OnBoarding
{
    OnBoardingShortcutsWindowPresenter::OnBoardingShortcutsWindowPresenter(app::ApplicationCommon *app)
    {
        initLayoutOptions();
    }

    std::vector<gui::Item *> OnBoardingShortcutsWindowPresenter::getLayouts() const
    {
        return layoutOptions;
    }

    gui::Item *OnBoardingShortcutsWindowPresenter::getFirstLayout() const
    {
        return layoutOptions.empty() ? nullptr : layoutOptions.front();
    }

    bool OnBoardingShortcutsWindowPresenter::isLastLayout(const gui::Item *layout) const
    {
        return !layoutOptions.empty() && layoutOptions.back() == layout;
    }

    bool OnBoardingShortcutsWindowPresenter::isOneOfTwoLastLayouts(const gui::Item *layout) const
    {
        return isLastLayout(layout) || (layoutOptions.size() >= 2 && layoutOptions[layoutOptions.size() - 2] == layout);
    }

    void OnBoardingShortcutsWindowPresenter::initLayoutOptions()
    {
        auto layoutsList = gui::factory::getLayouts();

        for (auto &layoutEntry : layoutsList) {
            layoutOptions.push_back(layoutEntry()->getLayout());
        }
    }
} // namespace app::OnBoarding
