/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    main.qml file handles loading and handling of functions which are
    accessible from all qml's.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 23/05/2023 - Initial version.
***************************************************************************/

import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import "./Core/Logic/Front_End_Logic/Action_Menu_Screens"
import "./Core/Logic/Front_End_Logic/Common_Logic"
import "./Core/Logic/Front_End_Logic/Login_Screens"
import "./Core/Logic/Front_End_Logic/Production_Screens"
import "./Core/Logic/Front_End_Logic/Recipe_Screens"
import "./Core/Logic/Front_End_Logic/Multi_Welder_Screens"
import "./Core/Logic/Front_End_Logic/Analytics_Screens"
import "./Core/Logic/Front_End_Logic/Platform_Config"
import "./Core/Logic/Front_End_Logic/System_screens"
import "./Core/Logic/Front_End_Logic/Diagnostics_Screens"
import "./Core/Logic/Front_End_Logic/Alarm_Screens"
import "./Core/Logic/Front_End_Logic/Actuator_Setup_Screens"

import Style 1.0
import NumpadDefine 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.RecipeEnum 1.0
import Com.Branson.SystemTypeDef 1.0

Window{
    id: mainWindow
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("UIController")
    //    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
    //    flags: Qt.FramelessWindowHint | Qt.Window
    visibility: Window.FullScreen

    /*1366 * 768 = 1280 * 800    1920 * 1080    800 * 480  */
    property int showWidth: (isRaspPI) ? 800 : 1024
    property int showHeight: (isRaspPI) ? 480 : 600

    property string qmltextTimeMode:                qsTr("Time")
    property string qmltextEnergyMode:              qsTr("Energy")
    property string qmltextPeakPowerMode:           qsTr("Peak Power")
    property string qmltextGroundDetectMode:        qsTr("Scrub Time")
    property string qmltextAbsoluteDistanceMode:    qsTr("Absolute Distance")
    property string qmltextCollapseDistanceMode:    qsTr("Collapse Distance")
    property string qmltextTimeModeUnit:                qsTr("")
    property string qmltextEnergyModeUnit:              qsTr("")
    property string qmltextPeakPowerModeUnit:           qsTr("")
    property string qmltextGroundDetectModeUnit:        qsTr("")
    property string qmltextAbsoluteDistanceModeUnit:    qsTr("")
    property string qmltextCollapseDistanceModeUnit:    qsTr("")

    property string qmltextInvalidInputWarning:    qsTr("Invalid inputs..!")
    property string qmltextWarningAccessDenied:    qsTr("Access Denied.")
    property string qmltextWarningHornRetract:    "The Actuator must be retracted before leaving the screen. Do you want to retract now ?"

    property string qmltextNoData : "NO DATA"
    property string qmltextNoDataMsg :  "No Data Available for this Cycle Counter."
    property bool   configurationFailed: true
    property int 	currentIndex : -1
    property bool isloaded: true
    property string qmltextactivewelderName:         "Welder "
    property string activeWelderNameTxt:           ""
    property bool isLoggedIn: false
    property bool isAlarmActive: false
    property bool isWarningActive: false
    property bool isNotificationActive: false
    property bool isServiceReminderActive: false

    property bool   isUserModifing           : false
    property bool   isUserModifingPassword   : false
    property bool isAutoLoginEnable: false
    property bool isAuthorityCheckEnable: true
    property bool isPasswordRestDongleInserted: false


    property string userNameTxt:           ""
    property string passwordTxt:           ""
    property string userLevelTxt:          ""
    property int 	currentActiveWindow : ActiveScreen.CurrentActiveScreen
    property string  userNameToDeleteReq : ""
    property string qmltextUserDeleteConfirm       : "Are you sure you want to delete ?"
	readonly property int dataLoggerMsgCounter : 3
	readonly property int idleTimeLogoutMaxVal : 2147483647   /* Time in milisecond and After conversion in days, it is 24 days*/
	readonly property int minuteToMilliSecTimeConvFact: 60000
	property bool bransonTabEnable: false
    property string qmltextInvalidValueMsg : qsTr("Invalid value is entered, Reverted to old value")

    property bool isOnPartActive: ActuatorSetupData.IsHornPositionOnGround

    property string qmltextPressureUnit:                ""
    property string qmltextDistanceUnit:                ""
    property string qmltextVelocityUnit:                ""
    property string qmltextForceUnit:                   ""
    property string qmltextTimeUnit:                    ""
    property string qmltextEnergyUnit:                  ""
    property string qmltextPowerUnit:                   ""
    property string qmltextFrequencyUnit:               ""
    property string qmltextPhaseUnit:                   ""
    property string qmltextCurrentUnit:                 ""
    property string qmltextAmplitudeUnit:               ""
    property string qmltextRequestAmplitudeUnit:        ""
    property string qmltextDownSpeedUnit:               ""

    property string qmltextExecutive:               "Executive"
    property string qmltextOperator:                "Operator"
    property string qmltextTechnician:              "Technician"
    property string qmltextSupervisor:              "Supervisor"

    property string qmltextContinueTxt:         "YES CONTINUE"
    property string qmltextSelRefGrphTxt:       "Selected Graph will be marked as a Reference Graph would you like to continue ?"
    property string qmltextReplaceTxt:          "REPLACE"
    property string qmltextMaxLimitTxt:         "Maximum limit to save reference graph is 3. Would you like to replace any of this existing reference graph ?"
    property string qmltextSuccessRefGrph:      " Successfully marked as a Reference Graph"
    property string qmltextOkTxt:               "OK"
    property string qmltextReplacedTxt:         " replaced as a reference graph with "
    property bool   opacityFlag : false
    property var qmlTextArray: [qmltextTimeMode, qmltextEnergyMode, qmltextPeakPowerMode,
        qmltextGroundDetectMode, qmltextAbsoluteDistanceMode, qmltextCollapseDistanceMode,
        qmltextTimeModeUnit, qmltextEnergyModeUnit, qmltextPeakPowerModeUnit, qmltextGroundDetectModeUnit, qmltextAbsoluteDistanceModeUnit,
        qmltextCollapseDistanceModeUnit]

   property var authorityLevelBaseModel:[("Executive"),("Operator")]
   property var authorityLevelAdvModel: [("Operator"), ("Technician"),("Supervisor") ,("Executive")]

    signal signalCurrentLanguageChanged()
    signal signalCurrentScreenChanged(int index)
    signal clearSubTabBar()
    signal activeAlarmDetailsListDataChanged()
    signal activeWarningDetailsListDataChanged()
    signal activeNotificationDetailsListDataChanged()
    signal activeServiceReminderDetailsListDataChanged()

    signal checkSuspectRejectSwitchButton(bool suspect ,bool reject, var suspectLow, var suspectHigh ,var rejectLow, var rejectHigh,  var decimals, var iunit)

    signal currentSelectedUserDetail( string buserId, string bauthorityLevel,  int bstatus, int bislocked )
    signal changePasswordSignal(string username)
    signal clrprevdataonChgnPass()
    signal sysConfigDataChanged()
    signal resetButtonAccess()
    signal loadRightActionModel()
    signal currentUnit(var unit)
    signal eStopEventOccurred()
	signal bransonKeyVerified()
    signal closeRightActionMenu()
signal loginUserNameAndUserLevelUpdated()

    QtObject
    {
        id: loginErrorEnum
        readonly property int param_LOGIN_ERROR_UNKNOWN               : 0
        readonly property int param_LOGIN_SUCCESS                     : 1
        readonly property int param_INVALID_USER_NAME_OR_PASSWORD     : 2
        readonly property int param_USER_LOCKED                       : 3
        readonly property int param_USER_DISABLED                     : 4
        readonly property int param_PASSWORD_EXPIRED                  : 5
        readonly property int param_PASSWORD_WILL_EXPIRE_SOON         : 6
        readonly property int param_FIRST_TIME_LOGIN                  : 7
        readonly property int param_PASSWORD_NOT_EXPIRED              : 8
		readonly property int param_AUTHORITY_CHECK_DISABLE           : 9
        readonly property int param_TWO_UNSUCCESSFUL_LOGIN_ATTEMPT    :10
    }

    QtObject
    {
        id: eStopEventsEnum
        readonly property int eStopPressedEventOccurred    : 0
        readonly property int eStopReleasedEventOccurred   : 1
        readonly property int eStopResetSuccess            : 2
    }

    QtObject
    {
        id: enumParamIndex
        readonly property int weldAmplitudeIdx    : 10
        readonly property int weldPressureIdx     : 11
        readonly property int weldFlowRateIdx     : 12
        readonly property int weldHoldTimeIdx     : 13
        readonly property int weldTriggerForceIdx : 14
        readonly property int weldHoldPressureIdx : 15
    }

    QtObject
    {
        id: refGraphOperationEnum
        readonly property int setRefGraph     : 1
        readonly property int replaceRefGraph : 2
        readonly property int successRefGraph : 3
    }

    Component.onCompleted: {

        console.log("Completed!")
        //            VirtualKeyboardSettings.locale = sysconfig.getLanguageCode()
        //            VirtualKeyboardSettings.locale = "en_US"
    }


    Connections
    {
        target: UnitConversion
        function onCurrentUnitChanged()
        {
            qmltextTimeModeUnit =               UnitConversion.TimeUnit
            qmltextEnergyModeUnit=              UnitConversion.EnergyUnit
            qmltextPeakPowerModeUnit=           UnitConversion.PowerUnit
            qmltextGroundDetectModeUnit=        UnitConversion.TimeUnit
            qmltextAbsoluteDistanceModeUnit=    UnitConversion.DistanceUnit
            qmltextCollapseDistanceModeUnit=    UnitConversion.DistanceUnit

            qmltextPressureUnit =         UnitConversion.PressureUnit
            qmltextDistanceUnit =         UnitConversion.DistanceUnit
            qmltextVelocityUnit =         UnitConversion.VelocityUnit
            qmltextForceUnit =            UnitConversion.ForceUnit
            qmltextTimeUnit =             UnitConversion.TimeUnit
            qmltextEnergyUnit =           UnitConversion.EnergyUnit
            qmltextPowerUnit =            UnitConversion.PowerUnit
            qmltextFrequencyUnit =        UnitConversion.FrequencyUnit
            qmltextPhaseUnit =            UnitConversion.PhaseUnit
            qmltextCurrentUnit =          UnitConversion.CurrentUnit
            qmltextAmplitudeUnit =        UnitConversion.AmplitudeUnit
            qmltextRequestAmplitudeUnit = UnitConversion.RequestAmplitudeUnit
            qmltextDownSpeedUnit = UnitConversion.DownSpeedUnit
            currentUnit(UnitConversion.currentUnit())
        }
    }

    ListModel
    {
        id:dataLoggerModel
    }

    Connections
    {
        target: DataLoggerLogic
        function onDataLoggerMsgChanged()
        {
			var counter = 0
            var dataLoggerMsgList = DataLoggerLogic.DataLoggerList
			dataLoggerMsgList = dataLoggerMsgList.slice(-3)
            dataLoggerModel.clear()
            for (var i = 0; i < dataLoggerMsgList.length; i++)
            {
				counter = counter + 1
				if(counter <= dataLoggerMsgCounter)
				{
					dataLoggerModel.append({name: dataLoggerMsgList[i]});
				}
            }
            showDataLoggerPopup()
        }
    }
	Connections
    {
        target: IdleTimeLogout
        function onIdleTimeLogOut()
        {
			mainWindow.logoutProcess()
        }
    }
    function getWeldModeText(modeIdx)
    {
        var qmltextWeldMode = ""
        switch(modeIdx)
        {
        case RecipeEnum.TIME_IDX:
            qmltextWeldMode = qmltextTimeMode
            break;
        case RecipeEnum.ENERGY_IDX:
            qmltextWeldMode = qmltextEnergyMode
            break;
        case RecipeEnum.PEAKPOWER_IDX:
            qmltextWeldMode = qmltextPeakPowerMode
            break;
        case RecipeEnum.GROUND_IDX:
            qmltextWeldMode = qmltextGroundDetectMode
            break;
        case RecipeEnum.ABSDISTANCE_IDX:
            qmltextWeldMode = qmltextAbsoluteDistanceMode
            break;
        case RecipeEnum.COLDISTANCE_IDX:
            qmltextWeldMode = qmltextCollapseDistanceMode
            break;
        default:
            qmltextWeldMode = qmltextTimeMode
            break;
        }
        return qmltextWeldMode
    }

    /*Return the unit value based on weld mode selected*/
    function getWeldModeUnit(modeIdx)
    {
        var qmltextWeldModeUnit = ""
        switch(modeIdx)
        {
        case RecipeEnum.TIME_IDX:
            qmltextWeldModeUnit = UnitConversion.TimeUnit
            break;
        case RecipeEnum.ENERGY_IDX:
            qmltextWeldModeUnit = UnitConversion.EnergyUnit
            break;
        case RecipeEnum.PEAKPOWER_IDX:
            qmltextWeldModeUnit = UnitConversion.PowerUnit
            break;
        case RecipeEnum.GROUND_IDX:
            qmltextWeldModeUnit = UnitConversion.TimeUnit
            break;
        case RecipeEnum.ABSDISTANCE_IDX:
            qmltextWeldModeUnit = UnitConversion.DistanceUnit
            break;
        case RecipeEnum.COLDISTANCE_IDX:
            qmltextWeldModeUnit = UnitConversion.DistanceUnit
            break;
        default:
            qmltextWeldModeUnit = UnitConversion.TimeUnit
            break;
        }
        return qmltextWeldModeUnit
    }

    function showChangePasswordScreen()
    {
        changePasswordScreen.visible = true
    }
    function closeChangePasswordScreen()
    {
        changePasswordScreen.visible = false
    }
    function showFullScreenChart()
    {
        chartViewFullScreen.visible = true
    }

    function hideFullScreenChart()
    {
        chartViewFullScreen.visible = false
    }

    function showLeftActionMenu()
    {
        leftMenuLoader.item.leftActionAnimation.restart()
        loadRightActionModel()
    }

    function hideLeftActionMenu()
    {
        leftMenuLoader.item.leftActionAnimationReturn.restart()
    }

    function showRightActionMenu()
    {
        rightMenuLoader.item.rightActionAnimation.restart()
        loadRightActionModel()
    }

    function hideRightActionMenu()
    {
        rightMenuLoader.item.rightActionAnimationReturn.restart()
    }

    function showMainWindowOpacity()
    {
        enableMainWindowOpacity.start()
    }

    function hideMainWindowOpacity()
    {
        disableMainWindowOpacity.start()
    }

    function showLanguageView()
    {
        languageSelectView.visible = true
    }

    function showBransonPopup(str,str2)
    {
        warningPopup.qmltextWarningDialog = str
        warningPopup.visible = true
        warningPopup.qmltextLabel = str2
        opacityFlag = true
    }

    function showBransonReadOnlyPopup(str,str2)
    {
        warningReadOnlyPopup.qmltextWarningDialog = str
        warningReadOnlyPopup.visible = true
        warningReadOnlyPopup.qmltextLabel = str2
        opacityFlag = true
    }

    function hideBransonReadOnlyPopup()
    {
        warningReadOnlyPopup.visible = false

        /*Opacity handled when multiple popups are visible at a time*/
        if((! dataLoggerPopup.visible) && (! warningPopup.visible))
        {
            opacityFlag = false
        }
    }

    function showDataLoggerPopup()
    {
        dataLoggerPopup.qmltextWarningDialog = dataLoggerModel.get(dataLoggerModel.count-1).name
        dataLoggerPopup.visible = true
    }

    function showBransonUnitChangePopup()
    {
        unitChangePopup.visible = true
        opacityFlag = true
    }

    function showReferenceGraphPopup(requestType, weldResultIndex, selectedCycleNo)
    {
        if(requestType === refGraphOperationEnum.setRefGraph) // To set first 3 reference graph.
        {
            refGraphPopup.visible = true
            refGraphPopup.isMultiButtonPopup = true
            refGraphPopup.qmltextYesContinueorReplace = qmltextContinueTxt
            refGraphPopup.height = mainWindow.showHeight * 0.5
            refGraphPopup.width = mainWindow.showWidth * 0.75
            refGraphPopup.showSuccessMsgText = false
            refGraphPopup.showRadioButtons = false
            refGraphPopup.showCancelButton = true
            refGraphPopup.showGreyRect = false
            refGraphPopup.newReferenceWeldResultIndex = weldResultIndex
            refGraphPopup.qmltextWarningDialog = qmltextSelRefGrphTxt
        }

        else if(requestType === refGraphOperationEnum.replaceRefGraph) //To replace the existing reference graph with new one.
        {
            refGraphPopup.visible = true
            refGraphPopup.isMultiButtonPopup = true
            refGraphPopup.qmltextWarningDialog = qmltextMaxLimitTxt
            refGraphPopup.height = mainWindow.showHeight * 0.5
            refGraphPopup.width = mainWindow.showWidth * 0.75
            refGraphPopup.showSuccessMsgText = false
            refGraphPopup.showRadioButtons = true
            refGraphPopup.showCancelButton = true
            refGraphPopup.showGreyRect = true
            refGraphPopup.newReferenceWeldResultIndex = weldResultIndex
            refGraphPopup.qmltextYesContinueorReplace = qmltextReplaceTxt
        }

        else if(requestType === refGraphOperationEnum.successRefGraph) // To show popup for Successfully replaced reference graph.
        {
            refGraphPopup.visible = true
            refGraphPopup.isMultiButtonPopup = true
            refGraphPopup.qmltextWarningDialog = selectedCycleNo + qmltextSuccessRefGrph
            refGraphPopup.height = mainWindow.showHeight * 0.5
            refGraphPopup.width = mainWindow.showWidth * 0.75
            refGraphPopup.showSuccessMsgText = true
            refGraphPopup.showCancelButton = false
            refGraphPopup.showRadioButtons = false
            refGraphPopup.showGreyRect = true
            refGraphPopup.qmltextSuccessText = selectedCycleNo + qmltextReplacedTxt
            refGraphPopup.newReferenceWeldResultIndex = weldResultIndex
            refGraphPopup.qmltextYesContinueorReplace = qmltextOkTxt
        }

        opacityFlag = true
    }

    function showBransonPopupForAccessDenied()
    {
        accessDenied.qmltextWarningDialog = qmltextWarningAccessDenied
        accessDenied.visible = true
    }

    function showBransonPopupForLockedScreen(str)
    {
        accessDenied.qmltextWarningDialog = str
        accessDenied.visible = true
    }

    function showBransonPopupForDel(str)
    {
        userNameToDeleteReq = str
        deletewarningPopup.isMultiButtonPopup = true
        deletewarningPopup.qmltextWarningDialog = qmltextUserDeleteConfirm
        deletewarningPopup.visible = true
        opacityFlag = true
    }

    function showBransonPopupForHornRetract()
    {
        onPartNotifier.isMultiButtonPopup = true
        onPartNotifier.qmltextWarningDialog = qmltextWarningHornRetract
        onPartNotifier. qmltextOk = "Done"
        onPartNotifier.visible = true
    }

    function getUserLevelModel()
    {
        if(SystemConfiguration.UserAccessLevelType === SystemTypeDef.STANDARD_USER_ACCESS_LEVEL)
        {
            return authorityLevelBaseModel
        }
        else
        {
            return authorityLevelAdvModel
        }
    }
	
	function showBransonScreen()
	{
		bransonKeyVerified()
	}

    function loginProcess()
    {
        isloaded = false

        switch(LoginObj.loginValidationFromASC()/*loginErrorEnum.param_LOGIN_SUCCESS*/)
        {

        case loginErrorEnum.param_LOGIN_SUCCESS:
            loginLayout.visible = false
            clearStackView()
            configLayout.visible =false
            // configurationFailed = false
            isLoggedIn = true
            menuParentOptionSelect(UIScreenEnum.PRODUCTION)
            loginUserNameAndUserLevelUpdated()
           setLogoutTimer()
            break;
        case loginErrorEnum.param_INVALID_USER_NAME_OR_PASSWORD:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            break;
        case loginErrorEnum.param_USER_LOCKED:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            break;
        case loginErrorEnum.param_USER_DISABLED:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            break;
        case loginErrorEnum.param_PASSWORD_EXPIRED:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            mainWindow.showChangePasswordScreen()
            break;
        case loginErrorEnum.param_PASSWORD_WILL_EXPIRE_SOON:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            loginLayout.visible = false
            clearStackView()
            configLayout.visible =false
            menuParentOptionSelect(UIScreenEnum.PRODUCTION)
            break;
        case loginErrorEnum.param_FIRST_TIME_LOGIN:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            mainWindow.showChangePasswordScreen()
            break;
        case loginErrorEnum.param_PASSWORD_NOT_EXPIRED:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            break;
		case loginErrorEnum.param_AUTHORITY_CHECK_DISABLE:
			warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
			warningPopup.visible = true
			break;
        case loginErrorEnum.param_TWO_UNSUCCESSFUL_LOGIN_ATTEMPT:
            warningPopup.qmltextWarningDialog = LoginObj.loginWarningMessages()
            warningPopup.visible = true
            break;
        default:
            console.log("Login Error Unknown")
        }
        mainWindow.hideMainWindowOpacity()

        /*Update the notification source type*/
        ActiveAlarmDetailsListModel.IsNotificationSystemGenerated = true
        ActiveAlarmDetailsListModel.loadActiveAlarmDetailsList()
        ActiveServiceReminderDetailsListModel.loadActiveServiceReminderDetailsList()

        /*Display the popup based on availability*/
        if(isAlarmActive)
        {
           alarmsPopup.visible = true
        }

        else if(isWarningActive)
        {
            warningsPopup.visible = true
        }

        else if(isNotificationActive)
        {
            notificationsPopup.visible = true
        }

        else if(isServiceReminderActive)
        {
           serviceReminderPopup.visible = true
        }
    }

    function logoutProcess()
    {
        LoginObj.onLogoutButtonClicked()
        loginLayout.visible = true
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.LOGIN
        mainWindow.hideMainWindowOpacity()
        clearStackView()
        closeRightActionMenu()
        isLoggedIn = false
        userMgmtAddUserScreen.visible = false
        opacityFlag = false
    }

    function exitApplication()
    {

        loginLayout.visible = true
        ActiveScreen.CurrentActiveScreen = UIScreenEnum.LOGIN
        mainWindow.hideMainWindowOpacity()
        clearStackView()
        userMgmtAddUserScreen.visible = false
        opacityFlag = false
    }

    function clearStackView()
    {
        stackMainView.pop(StackView.Immediate)
        stackMainView.clear()
        headerLoader.item.clearChildrenTitleModel()
    }

    function setHeaderTitle(menuName, menuIndex)
    {
        headerLoader.item.appendChildrenTitleModel(menuName, menuIndex)
    }

    function clearHeaderTitle( menuIndex)
    {
        headerLoader.item.clearChildrenTitleModelLab(menuIndex)
    }

    function menuParentOptionSelect(menuIndex)
    {
        if (!configurationFailed)
        {
            clearStackView()
            switch(menuIndex)
            {
            case UIScreenEnum.RECIPES:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.PRODUCTION:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Production_Screens/productionWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.ANALYTICS:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Analytics_Screens/AnalyticsWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.SYSTEM:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/systemWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.ACTUATORSETUP:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Actuator_Setup_Screens/ActuatorSetupWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.DIAGNOSTICS:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/DiagnosticsWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationWindow.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.GENERATEREPORT:
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReport.qml", {}, StackView.Immediate)
                break;
            case UIScreenEnum.IMPORTEXPORT:
                break;
            default:
                break;
            }
        }
    }

    function menuChildOptionSelect(parentMenuIndex, childMenuIndex)
    {
        switch(parentMenuIndex)
        {
        case UIScreenEnum.RECIPES:
            if(childMenuIndex === UIScreenEnum.RECIPES_LAB)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Recipe_Screens/recipeLabWindow.qml", {}, StackView.Immediate)
            }

            break;

        case UIScreenEnum.SYSTEM:
            if(childMenuIndex === UIScreenEnum.SYSTEM_CONFIG)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/systemConfigurationWindow.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_INFO)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/systemInformationWindow.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_SERVICE_COUNT)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/ServiceCount.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/Calibration.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrationActuator.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_FULL_SYSTEM)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrateFullSystem.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_ACTUATOR_WITH_START_SWITCHES)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrationActuatorWithStartSwitches.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_FORCE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrationForce.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_PRESSURE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrationPressure.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_RESET_SENSORS)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrationResetSensors.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.SYSTEM_CALIBRATE_SENSORS)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/System_screens/CalibrationSensors.qml", {}, StackView.Immediate)
            }
            break;

        case UIScreenEnum.DIAGNOSTICS :
            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_SCAN)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/Scan.qml", {}, StackView.Immediate)
            }

            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_SCAN_RECIPE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/ScanRecipe.qml", {}, StackView.Immediate)
            }

            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_TEST)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/Test.qml", {}, StackView.Immediate)
            }

            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_TEST_RECIPE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/TestRecipe.qml", {}, StackView.Immediate)
            }

            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_SEEK)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/Seek.qml", {}, StackView.Immediate)
            }

            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_SEEK_RECIPE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/SeekRecipe.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_EVENT)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/EventLog.qml", {}, StackView.Immediate)
            }

            if(childMenuIndex === UIScreenEnum.DIAGNOSTICS_ALARM)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/AlarmEventsLog.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.DIAGNOSTIC_USERIO)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Diagnostics_Screens/DiagnosticUserIO.qml", {}, StackView.Immediate)
            }

            break;
        case UIScreenEnum.GENERATEREPORT:
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReport.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_STORAGE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportStorageOpt.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_DATA_FILTERS)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportDataFilters.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_SUMMARY)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportSummary.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_POPUP)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportPopup.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_CONTINUOUS_STORAGE)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportContinuousStoregeOpt.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_CONTINUOUS_DATA_FILTER)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportContinuosDataFilter.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.GENERATE_REPORT_CONTINUOUS_SUMMARY)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Generate_Report/GenerateReportContinuosSummary.qml", {}, StackView.Immediate)
            }
        case UIScreenEnum.ANALYTICS:
            if(childMenuIndex === UIScreenEnum.ANALYTICS_RESULT_TABLE_VIEW)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Analytics_Screens/AnalyticsResultTable.qml", {}, StackView.Immediate)
            }
            if(childMenuIndex === UIScreenEnum.ANALYTICS_RESULT_GRAPH_VIEW)
            {
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Analytics_Screens/AnalyticsWindow.qml", {}, StackView.Immediate)
            }

            break;

        default:
            break;
        }
    }

    function menuOptionLookAt(index)
    {
        var objItem = stackMainView.find(function(item) { return (item.qmlscreenIndicator === index)})
        if(objItem !== null)
        {
            var size = stackMainView.depth
            while((stackMainView.get(size - 1) !== objItem) && (size > 0))
            {
                stackMainView.pop(StackView.Immediate)
                size = stackMainView.depth
            }
        }
    }

    function showPrimaryNumpad(strTitle, strUnit, iDecimals, realMinimum, realMaximum, strCurrentValue)
    {
        primaryNumpad.headertext = strTitle
        primaryNumpad.suffix = strUnit
        primaryNumpad.decimals = iDecimals
        primaryNumpad.minimumValue = realMinimum
        primaryNumpad.maximumValue = realMaximum
        primaryNumpad.value = strCurrentValue
        primaryNumpad.visible = true
    }


    function showMinMaxNumpad(strTitle, isMultiMinMax, iFirstYAxisEnum, iSecondYAxisEnum)
    {
        minMaxNumpad.headerText = strTitle
        minMaxNumpad.isMultiMinMaxNumpad = isMultiMinMax

        if(isMultiMinMax)
        {
            minMaxNumpad.firstYAxisSelectedEnum = iFirstYAxisEnum
            minMaxNumpad.secondYAxisSelectedEnum = iSecondYAxisEnum
        }

        minMaxNumpad.visible = true
    }

    function showSuspectRejectNumpad(strTitle, bSuspectCheck, bRejectCheck, realSuspectLow, realRejectLow, realSuspectHigh,
                                     realRejectHigh, iDecimals , minimumSuspectLow ,minimumRejectLow ,maximumSuspectHigh, maximumRejectHigh, unit)
    {

        suspectRejectNumpad.headerText = strTitle
        suspectRejectNumpad.suspectChecked = bSuspectCheck
        suspectRejectNumpad.rejectChecked = bRejectCheck
        suspectRejectNumpad.suspectLow = realSuspectLow
        suspectRejectNumpad.rejectLow = realRejectLow
        suspectRejectNumpad.suspectHigh = realSuspectHigh
        suspectRejectNumpad.rejectHigh = realRejectHigh
        suspectRejectNumpad.decimals = iDecimals
        suspectRejectNumpad.suspectLowMinRange = minimumSuspectLow
        suspectRejectNumpad.rejectLowMinRange = minimumRejectLow
        suspectRejectNumpad.suspectLowMaxRange = maximumSuspectHigh
        suspectRejectNumpad.rejectLowMaxRange = maximumRejectHigh
        suspectRejectNumpad.suffix = unit
        checkSuspectRejectSwitchButton(bSuspectCheck ,bRejectCheck,realSuspectLow, realSuspectHigh, realRejectLow, realRejectHigh, iDecimals, unit)
        suspectRejectNumpad.visible = true
    }

    function showSteppingAmplitudeNumpad(strTitle, strUnit, iDecimals, realMinimum, realMaximum, strCurrentValue)
    {
        steppingAmplitudeNumpad.headertext = strTitle
        steppingAmplitudeNumpad.suffix = strUnit
        steppingAmplitudeNumpad.value = strCurrentValue
        steppingAmplitudeNumpad.decimals = iDecimals
        steppingAmplitudeNumpad.minimumValue = RecipeLabData.getMinParamValue(enumParamIndex.weldAmplitudeIdx)
        steppingAmplitudeNumpad.maximumValue = RecipeLabData.getMaxParamValue(enumParamIndex.weldAmplitudeIdx)
        steppingAmplitudeNumpad.visible = true
    }

    function showSteppingPressureNumpad(strTitle, strUnit, iDecimals, realMinimum, realMaximum, strCurrentValue)
    {
        steppingPressureNumpad.headertext = strTitle
        steppingPressureNumpad.suffix = strUnit
        steppingPressureNumpad.value = strCurrentValue
        steppingPressureNumpad.decimals = iDecimals
        steppingPressureNumpad.minimumValue = realMinimum
        steppingPressureNumpad.maximumValue = realMaximum
        steppingPressureNumpad.visible = true
    }

    function showRecipeCopyNumpad(iSourceRecipeNo)
    {
        recipeCopyNumpad.sourceRecipeNo = iSourceRecipeNo
        recipeCopyNumpad.visible = true
    }

    function showSoftwareUpgrade()
    {
        softwareUpgrade.visible = true
    }

    function showMultiWelderInformation()
    {
        multiWelderInformation.visible=true
    }

    function showConfigurationUpgrade()
    {
        configUpgrade.visible = true
    }

    function showDisconnectionAlert()
    {
        alertWindow.visible = true
    }

    function showMessagePopUp()
    {
        messagePopup.visible = true
        opacityFlag = true
    }

    function showUserMgmtAddUserScreen(buserId, bauthorityLevel, bstatus, bislocked )
    {
        userMgmtAddUserScreen.visible=true
        var comboboxIndex = -1
        var statusVal = -1

        if(bstatus === "Enable")
        {
            statusVal = 0
        }
        else if(bstatus === "Disable")
        {
            statusVal = 1
        }

        if(bauthorityLevel === "Executive")
        {
            comboboxIndex = 3
        }
        else if(bauthorityLevel === "Operator")
        {
            comboboxIndex = 0
        }
        else if(bauthorityLevel === "Technician")
        {
            comboboxIndex = 1
        }
        else if(bauthorityLevel === "Supervisor")
        {
            comboboxIndex = 2
        }

        userMgmtAddUserScreen.userId =buserId
        userMgmtAddUserScreen.authorityLevel =bauthorityLevel
        userMgmtAddUserScreen.status =statusVal
        userMgmtAddUserScreen.islocked =bislocked
        userMgmtAddUserScreen.password =""
        userMgmtAddUserScreen.confrmPass =""
        currentSelectedUserDetail(buserId, bauthorityLevel, statusVal, bislocked)
        opacityFlag = true
    }

    function showChooseParametersView()
    {
        chooseParametersView.visible = true
    }

    function showResetPasswordPopup()
    {
        userResetPasswordPopup.visible = true
        clrprevdataonChgnPass()
    }

    function showChangePasswordPopup( userName)
    {
        var usrName = userName
        userChangePasswordPopup.visible = true
        changePasswordSignal(usrName)
        opacityFlag = true
    }

    function showChangeCnnectionStatus()
    {
        multiWelderInterface.setActiveWelder(currentIndex)
    }

    function showBransonService()
    {
        boardReplacePopup.visible = true
    }

    function showBransonWritablePopup(alarmLogIndex)
    {
        bransonWritablePopup.index = alarmLogIndex
        bransonWritablePopup.visible = true
    }

	function setLogoutTimer()
    {
        var timeOutSetInMin = LoginObj.getIdleLogOffTime()
		var authCheck = LoginObj.getUpdatedAuthCheck()
		if(timeOutSetInMin !== 0 && (authCheck === true))
		{
			var timeOutInMilliseconds = minuteToMilliSecTimeConvFact * timeOutSetInMin;
			IdleTimeLogout.setTimeOut(timeOutInMilliseconds);
		}
		else
		{
			IdleTimeLogout.setTimeOut(mainWindow.idleTimeLogoutMaxVal);
		}
    }


    // Slot get called on welder index changed or configuration status updated.
    Connections
    {
        target: configStatus
        function onPlatformConfigStateUpdated(Status)
        {
            showChangeCnnectionStatus()
            if (Status === 2)
            {
                configurationFailed = false
                clearStackView()
                if(LoginObj.passwordOverrideStatusRead() === false)
                {
                    isPasswordRestDongleInserted = LoginObj.getPasswordOverrideStatus()
                }
                if(isPasswordRestDongleInserted === false)
                {
                    /*Processes checks if Authority check or Auto Login settings are configured.*/
                    if(LoginObj.autoLoginStatusRead() === false || LoginObj.authorityCheckStatusRead() === false)
                    {
                        isAutoLoginEnable = LoginObj.getAutoLoginStatus()

                        isAuthorityCheckEnable = LoginObj.getAuthorityCheckStatus()
                    }
                }
                 /*Checks if Auto login is configured or Authority check is configured.*/
                if((LoginObj.passwordOverrideStatusRead() && (isPasswordRestDongleInserted === true)) || (LoginObj.autoLoginStatusRead() === true) && (isAutoLoginEnable === true)
				  || (LoginObj.authorityCheckStatusRead() === true) && (isAuthorityCheckEnable === true))
                {
                    isloaded = false
					
					if((LoginObj.passwordOverrideStatusRead() === true) && (isPasswordRestDongleInserted === true))
					{
						loginLayout.visible = false
						clearStackView()
                        configLayout.visible = false
						menuParentOptionSelect(UIScreenEnum.SYSTEM_CONFIG_USERMANAGEMENT)
                        mainWindow.userNameTxt = "NA"
                        mainWindow.userLevelTxt = ""
					}
                    /*If Auto login is enabled then user must be login to Application without login process. */
                    else if((LoginObj.autoLoginStatusRead() === true) && (isAutoLoginEnable === true) && (isAuthorityCheckEnable === false))
                    {
                        loginLayout.visible = false
                        configLayout.visible = false
                        LoginObj.onAutoLoginRequest()
                    }
                    /*If Authority check is enabled then user must be able to enter Application without user name and password. */
                    else if((LoginObj.authorityCheckStatusRead() === true) && (isAuthorityCheckEnable === true))
                    {
                        loginLayout.visible = false
                        clearStackView()
                        configLayout.visible =false
                        menuParentOptionSelect(UIScreenEnum.PRODUCTION)
                        mainWindow.userNameTxt = "NA"
                        mainWindow.userLevelTxt = ""
                    }
                }
                /*If Auto Login Status is not enabled then show Login Page. */
                else if((LoginObj.autoLoginStatusRead() === true) && (isAutoLoginEnable === false))
                {
                    loginLayout.visible = true
                    menuParentOptionSelect(UIScreenEnum.LOGIN)
                }
                /*If Auto Login Status is not enabled then show Login Page. */
                else
                {

                    loginLayout.visible = true
                    menuParentOptionSelect(UIScreenEnum.LOGIN)
                }
            }
            else
            {
                configurationFailed = true
                clearStackView()
                stackMainView.push("qrc:/Core/Logic/Front_End_Logic/Platform_Config/ConfigStatus.qml", {}, StackView.Immediate)
            }
        }
    }

    Connections
    {
        target: leftMenuLoader.item
        function onActiveWelder(actv)
        {
            if (actv === -1)
            {
                activeWelderNameTxt = "No Welder"
            } else
            {
                activeWelderNameTxt = qmltextactivewelderName + " " + (actv+1)
            }
        }
    }

    Connections
    {
        target: LanguageConfig
        function onSignalCurrentLanguageChanged()
        {
            signalCurrentLanguageChanged()

            mainWindow.hideMainWindowOpacity()
            qmlTextArray = LanguageConfig.getLanguageStringList(UIScreenEnum.WELDMODE_VALUE_LOWERSTRING, qmlTextArray)
            qmltextTimeMode             = qmlTextArray[textEnum.timeModeIdx]
            qmltextEnergyMode           = qmlTextArray[textEnum.energyModeIdx]
            qmltextPeakPowerMode        = qmlTextArray[textEnum.peakPowerModeIdx]
            qmltextGroundDetectMode     = qmlTextArray[textEnum.groundDetectModeIdx]
            qmltextAbsoluteDistanceMode = qmlTextArray[textEnum.absoluteDistanceModeIdx]
            qmltextCollapseDistanceMode = qmlTextArray[textEnum.collapseDistanceModeIdx]
            qmltextTimeModeUnit             =  qmlTextArray[textEnum.timeModeUnitIdx]
            qmltextEnergyModeUnit           =  qmlTextArray[textEnum.energyModeUnitIdx]
            qmltextPeakPowerModeUnit        =  qmlTextArray[textEnum.peakPowerModeUnitIdx]
            qmltextGroundDetectModeUnit     =  qmlTextArray[textEnum.groundDetectModeUnitIdx]
            qmltextAbsoluteDistanceModeUnit =  qmlTextArray[textEnum.absoluteDistanceModeUnitIdx]
            qmltextCollapseDistanceModeUnit =  qmlTextArray[textEnum.collapseDistanceModeUnitIdx]

            NumpadDefine.updateLanguage()
            AxisDefine.updateLanguage()
            AlarmDefine.updateLanguage()
        }
    }

    Connections
    {
        target: headerLoader.item
        function onSignalCurrentScreenIndexChanged(index)
        {
            menuOptionLookAt(index)
            headerLoader.item.removeChildrenTitleModel(index)
            signalCurrentScreenChanged(index)
            /*Active screen update*/
            ActiveScreen.CurrentActiveScreen = index
            clearSubTabBar()
        }

        function onActiveAlarmPopupSelected()
        {
            /*Update the notification source type*/
            ActiveAlarmDetailsListModel.IsNotificationSystemGenerated = false
            ActiveAlarmDetailsListModel.loadActiveAlarmDetailsList()
            ActiveServiceReminderDetailsListModel.loadActiveServiceReminderDetailsList()

            userRequestedAlarmsPopup.visible = true
            resetButtonAccess()

        }
    }


    Connections
    {
        target: DisplayModesHMI
        function onCurrentDisplayModeChanged()
        {
            if(DisplayModesHMI.DisplayMode === SystemTypeDef.DISPLAY_MODE_LOCKED)
            {
                lockedmodescreen.visible = true
            }

            else
            {
                lockedmodescreen.visible = false
            }
        }

    }
    Connections
    {
        target: ActiveAlarmDetailsListModel
        function onActiveAlarmDetailsListDataChanged()
        {
            isAlarmActive = true

            /*Update the notification source type*/
            ActiveAlarmDetailsListModel.IsNotificationSystemGenerated = true
            ActiveAlarmDetailsListModel.loadActiveAlarmDetailsList()
            ActiveServiceReminderDetailsListModel.loadActiveServiceReminderDetailsList()

            if(isLoggedIn)
            {
                alarmsPopup.visible = true
            }

            userRequestedAlarmsPopup.visible = false
        }

        function onActiveWarningDetailsListDataChanged()
        {
            isWarningActive = true

            /*Update the notification source type*/
            ActiveAlarmDetailsListModel.IsNotificationSystemGenerated = true
            ActiveAlarmDetailsListModel.loadActiveAlarmDetailsList()
            ActiveServiceReminderDetailsListModel.loadActiveServiceReminderDetailsList()

            if(isLoggedIn)
            {
                if((! isAlarmActive) && (! isNotificationActive) && (! isServiceReminderActive))
                {
                    warningsPopup.visible = true
                }
            }

            userRequestedAlarmsPopup.visible = false
        }

        function onActiveNotificationDetailsListDataChanged()
        {
            isNotificationActive = true
            /*Update the notification source type*/
            ActiveAlarmDetailsListModel.IsNotificationSystemGenerated = true
            ActiveAlarmDetailsListModel.loadActiveAlarmDetailsList()
            ActiveServiceReminderDetailsListModel.loadActiveServiceReminderDetailsList()

            if(isLoggedIn)
            {
                if((! isAlarmActive) && (! isWarningActive) && (! isServiceReminderActive))
                {
                    notificationsPopup.visible = true
                }
            }

            userRequestedAlarmsPopup.visible = false
        }

        function onActiveServiceReminderDetailsListDataChanged()
        {
            isServiceReminderActive = true
            /*Update the service reminder source type*/
            ActiveAlarmDetailsListModel.IsNotificationSystemGenerated = true
            ActiveAlarmDetailsListModel.loadActiveAlarmDetailsList()
            ActiveServiceReminderDetailsListModel.loadActiveServiceReminderDetailsList()

            if(isLoggedIn)
            {
                if((! isAlarmActive) && (! isWarningActive) && (! isNotificationActive))
                {
                    serviceReminderPopup.visible = true
                }
            }

            userRequestedAlarmsPopup.visible = false
        }

        function onEStopEventOccurred(eventType)
        {
            if(eventType === eStopEventsEnum.eStopPressedEventOccurred)
            {
                eStopPopup.visible = true
            }

            else if(eventType === eStopEventsEnum.eStopResetSuccess)
            {
                eStopPopup.visible = false
            }
        }
    }
	
	Connections
    {
        target: LoginObj
		function onLoadingDataChangedd()
		{
			if(isAutoLoginEnable === true)
			{
				mainWindow.userNameTxt = LoginObj.getAutoLoginUserName()
				mainWindow.userLevelTxt = LoginObj.getLoginUserLevel()
				mainWindow.loginProcess()
				UserPrivilegeObj.processUserPrivilige()
			}
		}
    }

    Connections
    {
        target: CycleDetailsListModel
        function onCycleNumberAlarmDataChanged()
        {
            showBransonPopup(qmltextNoDataMsg,qmltextNoData)
        }
    }
	

    QtObject
    {
        id: textEnum
        readonly property int timeModeIdx                   : 0
        readonly property int energyModeIdx                 : 1
        readonly property int peakPowerModeIdx              : 2
        readonly property int groundDetectModeIdx           : 3
        readonly property int absoluteDistanceModeIdx       : 4
        readonly property int collapseDistanceModeIdx       : 5
        readonly property int timeModeUnitIdx               : 6
        readonly property int energyModeUnitIdx             : 7
        readonly property int peakPowerModeUnitIdx          : 8
        readonly property int groundDetectModeUnitIdx       : 9
        readonly property int absoluteDistanceModeUnitIdx   : 10
        readonly property int collapseDistanceModeUnitIdx   : 11
    }

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: Style.backgroundColor
        Component.onCompleted:
        {
            if(debug === true)
            {
                if(Screen.width !== showWidth)
                {
                    if(Screen.width > 1279 && Screen.width < 1901) //1366 X 768 or 1280 X 800 10inches
                    {
                        console.debug("1366 X 768 10inches screen resolution:", Screen.width)
                        Style.scaleHint = 1.6
                        mainWindow.showWidth = Screen.width
                        mainWindow.showHeight = Screen.height
                    }
                    else if(Screen.width > 1900)    //1920 X 1080 biggest screen
                    {
                        console.debug("1920 x 1080 biggest screen resolution")
//                        Style.scaleHint = 2.4
//                        mainWindow.showWidth = Screen.width
//                        mainWindow.showHeight = Screen.height
                        Style.scaleHint = 1.0
                    }
                    else                            //800 X 480 7inches
                    {
                        console.debug("800 X 480 7inches screen")
                        Style.scaleHint = 1.0
                    }
                }
            }

            else
            {
                Style.scaleHint = Screen.width / showWidth;
                mainWindow.showWidth = Screen.width
                mainWindow.showHeight = Screen.height
            }

            var str = "Screen resolution:" + Screen.width + "X" + Screen.height
            console.debug(str)
            leftMenuLoader.source = ""
            leftMenuLoader.source = "qrc:/Core/Logic/Front_End_Logic/Action_Menu_Screens/leftActionMenu.qml"
            rightMenuLoader.source = ""
            rightMenuLoader.source = "qrc:/Core/Logic/Front_End_Logic/Action_Menu_Screens/rightActionMenu.qml"
        }
    }

    Item
    {
        id: windowArea
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
        visible: true
        Loader
        {
            id: headerLoader
            width: parent.width
            anchors.top: parent.top
            height: Math.round(50 * Style.scaleHint)
            source:  "qrc:/Core/Logic/Front_End_Logic/Common_Logic/header.qml"
        }

        Loader
        {
            id: footerLoader
            width: parent.width
            anchors.bottom: parent.bottom
            height: parent.height*0.06
            source:  "qrc:/Core/Logic/Front_End_Logic/Common_Logic/footer.qml"
        }

        Loader
        {
            id: leftMenuLoader
            anchors.left: headerLoader.left
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            z: 2
            //            source: "qrc:/Core/Logic/Front_End_Logic/leftActionMenu.qml"
        }

        Loader
        {
            id: rightMenuLoader
            anchors.right: headerLoader.right
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            z: 2
            //            source: "qrc:/Core/Logic/Front_End_Logic/rightActionMenu.qml"
        }

        StackView
        {
            id: stackMainView
            anchors.top: headerLoader.bottom
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.10
            width: parent.width
        }

        Rectangle
        {
            id: mainWindowOpacity
            anchors.centerIn: parent
            width: mainWindow.showWidth
            height: mainWindow.showHeight
            color: Style.mainWindowOpacityColor
            z: -1
            OpacityAnimator on opacity
            {
                id: enableMainWindowOpacity
                from: 0
                to: 0.5
                duration: 250
                target: mainWindowOpacity
                onRunningChanged: {
                    if(enableMainWindowOpacity.running)
                    {
                        mainWindowOpacity.z = 1
                    }
                }
            }

            OpacityAnimator on opacity
            {
                id: disableMainWindowOpacity
                from: 0.5
                to: 0
                duration: 250
                target: mainWindowOpacity
                onRunningChanged: {
                    if(disableMainWindowOpacity.running)
                    {
                        mainWindowOpacity.z = -1
                    }
                    else
                    {
                        mainWindowOpacity.z = -1
                    }
                }
            }
        }
    }


    ChooseParameters
    {
        id: chooseParametersView
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    TranslationView
    {
        id: languageSelectView
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    MultiWelderScreen
    {
        id:multiWelderInformation
        visible:false
        anchors.centerIn: parent
        focus:true
        width:mainWindow.showWidth*0.70
        height: mainWindow.showHeight*0.85
    }

    ConfigUpgrade
    {
        id:configUpgrade
        visible:false
        x: parent.width*0.30
        y:parent.height*0.15
        focus:true
        width:mainWindow.showWidth*0.35
        height: mainWindow.showHeight*0.35

        onVisibleChanged:
        {
            opacityFlag = visible
        }
    }
	
    SoftwareUpgrade
    {
        id:softwareUpgrade
        visible:false
		anchors.centerIn: parent
        focus:true
        width:mainWindow.showWidth*0.50
        height: mainWindow.showHeight*0.60

        onVisibleChanged:
        {
            opacityFlag = visible
        }
    }

    AlertWindow
    {
        id: alertWindow
        visible:false
        focus:true
        x:windowArea.width*0.35
        y:windowArea.height*0.09
        z: 6
        width: mainWindow.width*0.50
        height: mainWindow.height*0.45

        onVisibleChanged:
        {
            opacityFlag = visible
        }
    }

    /*Opacity effect rectangle*/
    Rectangle
    {
        id: opacityEffectRect
        z: 5
        visible: opacityFlag
        anchors.left: parent.Left
        anchors.top: parent.Top
        height: parent.height
        width: parent.width
        color: Style.opacityEffectColor
        opacity: 0.25

        MouseArea
        {
            id: opacityEffectRectMa
            anchors.fill: parent
            onClicked:
            {
                /*Avoid false click*/
            }
        }
    }

    BransonPrimaryNumpad
    {
        id: primaryNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonMinMaxNumpad
    {
        id: minMaxNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
        onInvalidInputsEntered:
        {
            warningPopup.qmltextWarningDialog = qmltextInvalidInputWarning
            warningPopup.visible = true
        }
    }

    BransonPopup
    {
        id: accessDenied
        onOKButtonClicked:
        {
            accessDenied.visible = false
            mainWindow.hideMainWindowOpacity()
        }
    }

    BransonPopup
    {
        id: warningPopup
        modal: true
        onOKButtonClicked:
        {
            warningPopup.visible = false

            if(! dataLoggerPopup.visible)
            {
                opacityFlag = false
            }
        }
        onCancelButtonClicked:
        {
            warningPopup.visible = false

            if(! dataLoggerPopup.visible)
            {
                opacityFlag = false
            }
        }
    }

    BransonReadOnlyPopup
    {
        id: warningReadOnlyPopup
        modal: true
    }

    BransonPopup
    {
        id: dataLoggerPopup
        onOKButtonClicked:
        {

            if(dataLoggerModel.count === 0 || dataLoggerModel.count === 1)
            {
                dataLoggerModel.remove(0)
                dataLoggerPopup.visible = false
            }

            else
            {
                dataLoggerModel.remove((dataLoggerModel.count - 1))
                showDataLoggerPopup();
            }
        }

        onCancelButtonClicked:
        {
            dataLoggerPopup.visible = false
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            opacityFlag = visible
        }
    }

    BransonPopup
    {
        id: deletewarningPopup
        onOKButtonClicked:
        {
            UserListDetailsListModel.onDeleteUserRequest(userNameToDeleteReq)

            deletewarningPopup.visible = false
            opacityFlag = false
        }
        onCancelButtonClicked:
        {
            deletewarningPopup.visible = false
            opacityFlag = false
        }
    }

    ReferenceGraphPopup
    {
        id: refGraphPopup
        anchors.centerIn: parent
        focus:true
        onOKButtonClicked:
        {
            refGraphPopup.visible = false
            opacityFlag = false
        }
        onCancelButtonClicked:
        {
            refGraphPopup.visible = false
            opacityFlag = false
        }
    }

    BransonUnitChangePopup
    {
        id:unitChangePopup
        onOKButtonClicked:
        {
            unitChangePopup.visible = false
            opacityFlag = false
        }
        onCancelButtonClicked:
        {
            unitChangePopup.visible = false
            opacityFlag = false
        }
    }

    BransonPopup
    {
        id: onPartNotifier
        onOKButtonClicked:
        {
            ActuatorSetupData.sendHornRetractRequest()
            onPartNotifier.visible = false
        }
        onCancelButtonClicked:
        {
            onPartNotifier.visible = false
        }
    }
    BransonSetupLimitNumpad
    {
        id: setupLimitNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonSuspectRejectNumpad
    {
        id:suspectRejectNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonControlLimitNumpad
    {
        id:controlLimitNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonSteppingAmplitudeNumpad
    {
        id:steppingAmplitudeNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonSteppingPressureNumpad
    {
        id:steppingPressureNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonRecipeCopyNumpad
    {
        id: recipeCopyNumpad
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    FullScreenGraphWindow
    {
        id: chartViewFullScreen
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    ConfigStatus
    {
        id: configLayout
        visible: true
        anchors.centerIn: parent
        width: mainWindow.width
        height: mainWindow.height
    }

    Login
    {
        id: loginLayout
        visible: false
        anchors.centerIn: parent
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    ChangePassword
    {
        id: changePasswordScreen
        visible: false
        anchors.centerIn: parent
        focus:true
        width: mainWindow.showWidth
        height: mainWindow.showHeight
    }

    BransonPopup
    {
        id: messagePopup
        visible: false
        anchors.centerIn: parent
        focus:true
        qmltextWarningDialog: qmltextInvalidValueMsg
        onOKButtonClicked:
        {
            messagePopup.visible = false
            opacityFlag = false
        }
        onCancelButtonClicked:
        {
            messagePopup.visible = false
            opacityFlag = false
        }
    }

    SystemConfigurationUserMgmtAddUser
    {
        id:userMgmtAddUserScreen
        visible:false
        anchors.centerIn: parent
        topMargin: Math.round(100 * Style.scaleHint)
        focus:true
        width:mainWindow.showWidth*0.50
        height: mainWindow.showHeight*0.698
    }

    SystemConfigurationUserListResetPassword
    {
        id:userResetPasswordPopup
        visible:false
        anchors.centerIn: parent
        topMargin: Math.round(90 * Style.scaleHint)
        focus:true
        width:mainWindow.showWidth * 0.50
        height: mainWindow.isUserModifingPassword ? mainWindow.showHeight*0.64 : mainWindow.showHeight*0.698
    }

    SystemConfigurationUserListChangePassword
    {
        id:userChangePasswordPopup
        visible:false
        anchors.centerIn: parent
        topMargin: Math.round(90 * Style.scaleHint)
        focus:true
        width:mainWindow.showWidth * 0.50
        height: mainWindow.isUserModifingPassword ? mainWindow.showHeight*0.64 : mainWindow.showHeight*0.698
    }

    BransonServiceBoardReplacePopup
    {
        id: boardReplacePopup

        onOKButtonClicked:
        {
            boardReplacePopup.visible = false
        }

        onCancelButtonClicked:
        {
            boardReplacePopup.visible = false
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            mainWindow.opacityFlag = visible
        }
    }

    BransonWritablePopup
    {
        id: bransonWritablePopup
        anchors.centerIn: parent

        onSavedButtonClicked:
        {
            bransonWritablePopup.visible = false
        }

        onCloseButtonClicked:
        {
            bransonWritablePopup.visible = false
        }

        /*Disable background touch*/
        onVisibleChanged:
        {
            mainWindow.opacityFlag = visible
        }
    }

    InputPanel {
        id: inputPanel
        visible: false
        z: 2
        y: windowArea.y + windowArea.height
        anchors.left: windowArea.left
        anchors.right: windowArea.right

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: windowArea.y + windowArea.height - inputPanel.height
                visible: false
            }
        }

        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.OutQuart
                }
            }
        }

        ActiveAlarmsPopup
        {
            id: alarmsPopup
            x: Math.round(150 * Style.scaleHint)
            y: Math.round(-475 * Style.scaleHint)
            width: mainWindow.showWidth * 0.60
            height: mainWindow.showHeight * 0.85
            visible: false
            onCloseButtonClicked:
            {
                alarmsPopup.visible = false
                isAlarmActive = false

                if(isWarningActive)
                {
                    warningsPopup.visible = true
                }

                else if(isNotificationActive)
                {
                   notificationsPopup.visible = true
                }

                else if(isServiceReminderActive)
                {
                   serviceReminderPopup.visible = true
                }
            }
        }

        ActiveWarningsPopup
        {
            id: warningsPopup
            x: Math.round(440 * Style.scaleHint)
            y: Math.round(-215 * Style.scaleHint)
            width: mainWindow.showWidth * 0.45
            height: mainWindow.showHeight * 0.45
            visible: false
            onCloseButtonClicked:
            {
                warningsPopup.visible = false
                isWarningActive = false

                if(isNotificationActive)
                {
                    notificationsPopup.visible = true
                }

                else if(isAlarmActive)
                {
                   alarmsPopup.visible = true
                }

                else if(isServiceReminderActive)
                {
                   serviceReminderPopup.visible = true
                }
            }
        }

        ActiveNotificationsPopup
        {
            id: notificationsPopup
            x: Math.round(440 * Style.scaleHint)
            y: Math.round(-215 * Style.scaleHint)
            width: mainWindow.showWidth * 0.45
            height: mainWindow.showHeight * 0.45
            visible: false
            onCloseButtonClicked:
            {
                notificationsPopup.visible = false
                isNotificationActive = false

                if(isAlarmActive)
                {
                    alarmsPopup.visible = true
                }

                else if(isWarningActive)
                {
                   warningsPopup.visible = true
                }

                else if(isServiceReminderActive)
                {
                   serviceReminderPopup.visible = true
                }
            }
        }

        ServiceReminderPopup
        {
            id: serviceReminderPopup
            x: Math.round(110 * Style.scaleHint)
            y: Math.round(-440 * Style.scaleHint)
            width: mainWindow.showWidth * 0.75
            height: mainWindow.showHeight * 0.80
            visible: false
            onCloseButtonClicked:
            {
                serviceReminderPopup.visible = false
                isServiceReminderActive = false

                if(isAlarmActive)
                {
                    alarmsPopup.visible = true
                }

                else if(isWarningActive)
                {
                   warningsPopup.visible = true
                }

                else if(isNotificationActive)
                {
                    notificationsPopup.visible = true
                }
            }
        }

        ActiveAlarmsPopupUserRequested
        {
            id: userRequestedAlarmsPopup
            x: Math.round(150 * Style.scaleHint)
            y: Math.round(-475 * Style.scaleHint)
            width: mainWindow.showWidth * 0.60
            height: mainWindow.showHeight * 0.85
            visible: false
            onCloseButtonClicked:
            {
                userRequestedAlarmsPopup.visible = false
            }
        }

        Component.onCompleted:
        {
//            VirtualKeyboardSettings.locale = sysconfig.getLanguageCode()
//            Style.scaleHint = 2
//            mainWindow.showWidth = Screen.width
//            mainWindow.showHeight = Screen.height
            // VirtualKeyboardSettings.locale = "en_US"
        }
    }

    EStopPopup
    {
        id: eStopPopup
        visible: false
        anchors.centerIn: parent.Center
        width: parent.width
        height: parent.height
    }

    LockedDisplayMode
    {
        id: lockedmodescreen
        visible: false
        anchors.fill: mainWindow
    }
}
