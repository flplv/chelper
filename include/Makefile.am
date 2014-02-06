include  $(top_srcdir)/PreRules.am

# These files will end up in the install include directory
# For example, /usr/include

shadowincludedir = $(includedir)/chelper

shadowinclude_HEADERS = \
    chelper/private_helper_types.h \
    chelper/checks.h \
    chelper/fast_ring_fifo.h \
    chelper/helper_types.h \
    chelper/log.h \
    chelper/my_string.h \
    chelper/number.h \
    chelper/ring_fifo.h \
    chelper/signalslot.h \
    chelper/signalslot2.h \
    chelper/signalslot_opaque.h \
    chelper/signalslot_data.h \
    chelper/timeout.h \
    chelper/vector.h \
    chelper/eventsystem.h \
    chelper/module_macros.h

uninstall-hook:
	rm -rf $(includedir)/chelper
