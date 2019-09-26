#############################################################################
# Makefile for building: battleship
# Generated by qmake (3.0) (Qt 5.3.1)
# Project:  battleship.pro
# Template: app
# Command: D:/GNUGCC/bin/qmake.exe -spec win32-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile battleship.pro
#############################################################################

MAKEFILE      = Makefile

first: debug
install: debug-install
uninstall: debug-uninstall
QMAKE         = D:/GNUGCC/bin/qmake.exe
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = cp -f
INSTALL_PROGRAM = cp -f
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = mv -f
SUBTARGETS    =  \
		debug \
		release


debug: FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: battleship.pro D:/GNUGCC/mkspecs/win32-g++/qmake.conf D:/GNUGCC/mkspecs/features/spec_pre.prf \
		D:/GNUGCC/mkspecs/qdevice.pri \
		D:/GNUGCC/mkspecs/features/device_config.prf \
		D:/GNUGCC/mkspecs/common/shell-unix.conf \
		D:/GNUGCC/mkspecs/qconfig.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_axbase.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_axbase_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_axcontainer.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_axcontainer_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_axserver.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_axserver_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_bluetooth.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_bluetooth_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_bootstrap_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_clucene_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_concurrent.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_concurrent_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_core.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_core_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_dbus.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_dbus_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_declarative.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_declarative_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_enginio.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_enginio_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_gui.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_gui_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_help.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_help_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_multimedia.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_multimedia_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_multimediawidgets.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_network.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_network_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_nfc.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_nfc_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_opengl.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_opengl_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_openglextensions.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_openglextensions_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_platformsupport_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_positioning.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_positioning_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_printsupport.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_printsupport_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_qml.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_qml_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_qmltest.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_qmltest_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_quick.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_quick_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_quickparticles_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_quickwidgets.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_script.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_script_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_scripttools.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_scripttools_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_sensors.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_sensors_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_serialport.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_serialport_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_sql.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_sql_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_svg.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_svg_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_testlib.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_testlib_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_uitools.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_uitools_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_websockets.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_websockets_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_widgets.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_widgets_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_winextras.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_winextras_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_xml.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_xml_private.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_xmlpatterns.pri \
		D:/GNUGCC/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		D:/GNUGCC/mkspecs/features/qt_functions.prf \
		D:/GNUGCC/mkspecs/features/qt_config.prf \
		D:/GNUGCC/mkspecs/features/win32/qt_config.prf \
		D:/GNUGCC/mkspecs/win32-g++/qmake.conf \
		D:/GNUGCC/mkspecs/features/spec_post.prf \
		D:/GNUGCC/mkspecs/features/exclusive_builds.prf \
		D:/GNUGCC/mkspecs/features/default_pre.prf \
		D:/GNUGCC/mkspecs/features/win32/default_pre.prf \
		D:/GNUGCC/mkspecs/features/resolve_config.prf \
		D:/GNUGCC/mkspecs/features/exclusive_builds_post.prf \
		D:/GNUGCC/mkspecs/features/default_post.prf \
		D:/GNUGCC/mkspecs/features/win32/console.prf \
		D:/GNUGCC/mkspecs/features/qml_debug.prf \
		D:/GNUGCC/mkspecs/features/win32/rtti.prf \
		D:/GNUGCC/mkspecs/features/precompile_header.prf \
		D:/GNUGCC/mkspecs/features/warn_on.prf \
		D:/GNUGCC/mkspecs/features/testcase_targets.prf \
		D:/GNUGCC/mkspecs/features/exceptions.prf \
		D:/GNUGCC/mkspecs/features/yacc.prf \
		D:/GNUGCC/mkspecs/features/lex.prf \
		battleship.pro
	$(QMAKE) -spec win32-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile battleship.pro
D:/GNUGCC/mkspecs/features/spec_pre.prf:
D:/GNUGCC/mkspecs/qdevice.pri:
D:/GNUGCC/mkspecs/features/device_config.prf:
D:/GNUGCC/mkspecs/common/shell-unix.conf:
D:/GNUGCC/mkspecs/qconfig.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_axbase.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_axbase_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_axcontainer.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_axcontainer_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_axserver.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_axserver_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_bluetooth.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_bluetooth_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_bootstrap_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_clucene_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_concurrent.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_concurrent_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_core.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_core_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_dbus.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_dbus_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_declarative.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_declarative_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_enginio.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_enginio_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_gui.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_gui_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_help.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_help_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_multimedia.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_multimedia_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_multimediawidgets.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_network.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_network_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_nfc.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_nfc_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_opengl.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_opengl_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_openglextensions.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_openglextensions_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_platformsupport_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_positioning.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_positioning_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_printsupport.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_printsupport_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_qml.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_qml_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_qmldevtools_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_qmltest.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_qmltest_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_quick.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_quick_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_quickparticles_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_quickwidgets.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_quickwidgets_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_script.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_script_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_scripttools.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_scripttools_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_sensors.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_sensors_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_serialport.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_serialport_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_sql.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_sql_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_svg.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_svg_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_testlib.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_testlib_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_uitools.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_uitools_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_websockets.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_websockets_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_widgets.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_widgets_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_winextras.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_winextras_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_xml.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_xml_private.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_xmlpatterns.pri:
D:/GNUGCC/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
D:/GNUGCC/mkspecs/features/qt_functions.prf:
D:/GNUGCC/mkspecs/features/qt_config.prf:
D:/GNUGCC/mkspecs/features/win32/qt_config.prf:
D:/GNUGCC/mkspecs/win32-g++/qmake.conf:
D:/GNUGCC/mkspecs/features/spec_post.prf:
D:/GNUGCC/mkspecs/features/exclusive_builds.prf:
D:/GNUGCC/mkspecs/features/default_pre.prf:
D:/GNUGCC/mkspecs/features/win32/default_pre.prf:
D:/GNUGCC/mkspecs/features/resolve_config.prf:
D:/GNUGCC/mkspecs/features/exclusive_builds_post.prf:
D:/GNUGCC/mkspecs/features/default_post.prf:
D:/GNUGCC/mkspecs/features/win32/console.prf:
D:/GNUGCC/mkspecs/features/qml_debug.prf:
D:/GNUGCC/mkspecs/features/win32/rtti.prf:
D:/GNUGCC/mkspecs/features/precompile_header.prf:
D:/GNUGCC/mkspecs/features/warn_on.prf:
D:/GNUGCC/mkspecs/features/testcase_targets.prf:
D:/GNUGCC/mkspecs/features/exceptions.prf:
D:/GNUGCC/mkspecs/features/yacc.prf:
D:/GNUGCC/mkspecs/features/lex.prf:
battleship.pro:
qmake: FORCE
	@$(QMAKE) -spec win32-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile battleship.pro

qmake_all: FORCE

make_first: debug-make_first release-make_first FORCE
all: debug-all release-all FORCE
clean: debug-clean release-clean FORCE
distclean: debug-distclean release-distclean FORCE
	-$(DEL_FILE) Makefile

check: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
