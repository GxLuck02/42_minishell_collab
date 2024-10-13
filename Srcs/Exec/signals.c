#include "../../Includes/minishell.h"


void handle_c(int sig)
{
    if (data->child_pid > 0)
    {
        // Si un processus enfant est en cours d'exécution, l'interrompre
        kill(data->child_pid, SIGINT);
    } else {
        // Sinon, afficher une nouvelle invite
        printf("\nShell> ");
        fflush(stdout);
    }

	
}