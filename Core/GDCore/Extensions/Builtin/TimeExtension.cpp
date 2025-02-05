/*
 * GDevelop Core
 * Copyright 2008-2016 Florian Rival (Florian.Rival@gmail.com). All rights
 * reserved. This project is released under the MIT License.
 */
#include "AllBuiltinExtensions.h"
#include "GDCore/Tools/Localization.h"

using namespace std;
namespace gd {

void GD_CORE_API BuiltinExtensionsImplementer::ImplementsTimeExtension(
    gd::PlatformExtension& extension) {
  extension
      .SetExtensionInformation(
          "BuiltinTime",
          _("Time"),
          "Actions and conditions to run timers, get the current time or "
          "modify the time scale (speed at which the game is running - useful "
          "for slow motion effects).",
          "Florian Rival",
          "Open source (MIT License)")
      .SetExtensionHelpPath("/all-features/timers");


  extension
      .AddCondition("Timer",
                    _("Value of a scene timer"),
                    _("Test the elapsed time of a scene timer."),
                    _("The timer _PARAM2_ is greater than _PARAM1_ seconds"),
                    _("Timers and time"),
                    "res/conditions/timer24.png",
                    "res/conditions/timer.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("expression", _("Time in seconds"))
      .AddParameter("string", _("Timer's name"));

  extension
      .AddCondition("TimeScale",
                    _("Time scale"),
                    _("Compare the time scale of the scene."),
                    _("the time scale of the scene"),
                    _("Timers and time"),
                    "res/conditions/time24.png",
                    "res/conditions/time.png")
      .AddCodeOnlyParameter("currentScene", "")
      .UseStandardRelationalOperatorParameters("number")
      .MarkAsAdvanced();

  extension
      .AddCondition("TimerPaused",
                    _("Scene timer paused"),
                    _("Test if the specified scene timer is paused."),
                    _("The timer _PARAM1_ is paused"),
                    _("Timers and time"),
                    "res/conditions/timerPaused24.png",
                    "res/conditions/timerPaused.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("string", _("Timer's name"))
      .MarkAsAdvanced();

  extension
      .AddAction(
          "ResetTimer",
          _("Start (or reset) a scene timer"),
          _("Reset the specified scene timer, if the timer doesn't exist "
            "it's created and started."),
          _("Reset the timer _PARAM1_"),
          _("Timers and time"),
          "res/actions/timer24.png",
          "res/actions/timer.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("string", _("Timer's name"));

  extension
      .AddAction("PauseTimer",
                 _("Pause a scene timer"),
                 _("Pause a scene timer."),
                 _("Pause timer _PARAM1_"),
                 _("Timers and time"),
                 "res/actions/pauseTimer24.png",
                 "res/actions/pauseTimer.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("string", _("Timer's name"))
      .MarkAsAdvanced();

  extension
      .AddAction("UnPauseTimer",
                 _("Unpause a scene timer"),
                 _("Unpause a scene timer."),
                 _("Unpause timer _PARAM1_"),
                 _("Timers and time"),
                 "res/actions/unPauseTimer24.png",
                 "res/actions/unPauseTimer.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("string", _("Timer's name"))
      .MarkAsAdvanced();

  extension
      .AddAction("RemoveTimer",
                 _("Delete a scene timer"),
                 _("Delete a scene timer from memory."),
                 _("Delete timer _PARAM1_ from memory"),
                 _("Timers and time"),
                 "res/actions/timer24.png",
                 "res/actions/timer.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("string", _("Timer's name"))
      .MarkAsAdvanced();

  extension
      .AddAction("ChangeTimeScale",
                 _("Change time scale"),
                 _("Change the time scale of the scene."),
                 _("Set the time scale of the scene to _PARAM1_"),
                 _("Timers and time"),
                 "res/actions/time24.png",
                 "res/actions/time.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("expression",
                    _("Scale (1: Default, 2: 2x faster, 0.5: 2x slower...)"));

  extension
      .AddExpression("TimeDelta",
                     _("Time elapsed since the last frame"),
                     _("Time elapsed since the last frame rendered on screen"),
                     _("Time"),
                     "res/actions/time.png")
      .AddCodeOnlyParameter("currentScene", "");

  extension
      .AddExpression("TempsFrame",
                     _("Time elapsed since the last frame"),
                     _("Time elapsed since the last frame rendered on screen"),
                     _("Time"),
                     "res/actions/time.png")
      .SetHidden()
      .AddCodeOnlyParameter("currentScene", "");

  extension
      .AddExpression("ElapsedTime",
                     _("Time elapsed since the last frame"),
                     _("Time elapsed since the last frame rendered on screen"),
                     _("Time"),
                     "res/actions/time.png")
      .SetHidden()
      .AddCodeOnlyParameter("currentScene", "");

  extension
      .AddExpression("TimerElapsedTime",
                     _("Scene timer value"),
                     _("Value of a scene timer"),
                     _("Time"),
                     "res/actions/time.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter("string", _("Timer's name"));

  extension
      .AddExpression("TimeFromStart",
                     _("Time elapsed since the beginning of the scene"),
                     _("Time elapsed since the beginning of the scene"),
                     _("Time"),
                     "res/actions/time.png")
      .AddCodeOnlyParameter("currentScene", "");

  extension
      .AddExpression("TempsDebut",
                     _("Time elapsed since the beginning of the scene"),
                     _("Time elapsed since the beginning of the scene"),
                     _("Time"),
                     "res/actions/time.png")
      .SetHidden()
      .AddCodeOnlyParameter("currentScene", "");

  extension
      .AddExpression("TimeScale",
                     _("Time scale"),
                     _("Returns the time scale of the scene."),
                     _("Time"),
                     "res/actions/time.png")
      .AddCodeOnlyParameter("currentScene", "");

  extension
      .AddExpression("Time",
                     _("Current time"),
                     _("Current time"),
                     _("Time"),
                     "res/actions/time.png")
      .AddCodeOnlyParameter("currentScene", "")
      .AddParameter(
          "stringWithSelector",
          _("Hour: hour - Minutes: min - Seconds: sec - Day of month: "
            "mday - Months since January: mon - Year since 1900: year - Days "
            "since Sunday: wday - Days since Jan 1st: yday - Timestamp (ms): "
            "timestamp\""),
          "[\"hour\", \"min\", \"sec\", \"mon\", \"year\", \"wday\", \"mday\", "
          "\"yday\", \"timestamp\"]");

}

}  // namespace gd
