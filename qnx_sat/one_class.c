/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */

#ifdef __USAGE
%C - instrumentation example

%C  - example that illustrates the very basic use of
      the TraceEvent() kernel call and the instrumentation
      module with tracelogger in a daemon mode.

      Only events from the thread class (_NTO_TRACE_THREAD)
      are monitored (intercepted).

      In order to use this example, start the tracelogger
      in the daemon mode as:

      tracelogger -n iter_number -d1

      with iter_number = your choice of 1 through 10

      After you start the example, tracelogger
      will log the specified number of iterations and then
      terminate. There are no messages printed upon successful
      completion of the example. You can view the intercepted
      events with the traceprinter utility.

      See accompanied documentation and comments within
      the sample source code for more explanations.
#endif

#include <sys/trace.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "instrex.h"

int main(int argc, char **argv)
{
	int fd;
    /*
     * Just in case, turn off all filters, since we
     * don't know their present state - go to the
     * known state of the filters.
     */
    printf("pid %d\n",getpid());	
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_DELALLCLASSES));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_KERCALL));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_KERCALL));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_THREAD));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_THREAD));
    
    //fd = open( "test",O_RDONLY);
    
    /*
     * Intercept only thread events
     */
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_PROCESS));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_KERCALL));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_SYSTEM));
     TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_CONTROL));
      TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_COMM));
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_USER));  
    /*
     * Start tracing process
     *
     * During the tracing process, the tracelogger (which
     * is being executed in daemon mode) will log all events.
     * You can specify the number of iterations (i.e., the
     * number of kernel buffers logged) when you start tracelogger.
     */
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_START));
    fd = open( "test",O_RDONLY);
    TRACE_EVENT(argv[0], TraceEvent(_NTO_TRACE_STOP));    
     /*
     * The main() of this execution flow returns.
     * However, the main() function of the tracelogger
     * will return after registering the specified number
     * of events.
     */
    return (0);
}
