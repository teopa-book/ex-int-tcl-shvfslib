#include <tcl.h>
#include <tclvfs.h>

#include <stdio.h>
#include <stdlib.h>

#define ZIPFS_VOLUME "//zipfs:/"
#define ZIPFS_APP_MOUNT ZIPFS_VOLUME "app"

static int is_interactive = 0;

int Tcl_AppInit(Tcl_Interp *interp)
{
    int rv = TclZipfs_MountBuffer(interp, tclvfs_zip, tclvfs_zip_len,
                                  ZIPFS_APP_MOUNT, 0);
    if (rv != TCL_OK) {
        fprintf(stderr, "fail to mount tcl libraries to %s\n", ZIPFS_APP_MOUNT);
        return TCL_ERROR;
    }

    Tcl_Obj *init_script = Tcl_GetStartupScript(NULL);
    if (init_script == NULL && !is_interactive) {
        init_script = Tcl_NewStringObj(ZIPFS_APP_MOUNT "/main.tcl", -1);
        Tcl_IncrRefCount(init_script);
        if (Tcl_FSAccess(init_script, 00) == 0) {
            Tcl_SetStartupScript(init_script, NULL);
        }
        Tcl_DecrRefCount(init_script);
    }

    if (Tcl_Init(interp) != TCL_OK) {
        fprintf(stderr, "fail to init tcl\n");
        return TCL_ERROR;
    }

    return TCL_OK;
}

int main(int argc, char *argv[])
{
    Tcl_Main(argc, argv, Tcl_AppInit);
    return 0;
}
