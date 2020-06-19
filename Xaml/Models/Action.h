#pragma once

#include "Models/Action.g.h"
#include "../PropertyChangedBase.hpp"

namespace winrt::TranslucentTB::Xaml::Models::implementation
{
	struct Action : ActionT<Action>, PropertyChangedBase<Action>
	{
		Action() = default;

		hstring Name();
		void Name(const hstring &value);

		hstring Description();
		void Description(const hstring &value);

		Windows::UI::Xaml::Controls::IconElement Icon();
		void Icon(const Windows::UI::Xaml::Controls::IconElement &value);

		event_token Click(const Windows::UI::Xaml::RoutedEventHandler &value);
		void Click(const event_token &token);

		void ForwardClick(const Windows::Foundation::IInspectable &sender, const Windows::UI::Xaml::RoutedEventArgs &args);

	private:
		hstring m_name;
		hstring m_description;
		Windows::UI::Xaml::Controls::IconElement m_icon = nullptr;
		event<Windows::UI::Xaml::RoutedEventHandler> m_click;
	};
}

namespace winrt::TranslucentTB::Xaml::Models::factory_implementation
{
	struct Action : ActionT<Action, implementation::Action>
	{
	};
}