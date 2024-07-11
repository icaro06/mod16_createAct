/*  Antonio Villanueva Segura
 *  Crée un fichier ACT par défaut,
 *  args le nom du fichier, le nombre d'alarmes, le nombre de commandes 
 *  et les espaces entre les alarmes et les commandes 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define USAGE "Crée un fichier ACT par défaut.\
ARGS le [1]nom du fichier, [2]le nombre d'alarmes, [3]le nombre de commandes \
et [5]les espaces entre les alarmes et les commandes"

void writeNumAlms(std::ofstream& salidaFile, int valor) {
    salidaFile << "NBR_ALM: " << valor << std::endl;
    salidaFile << std::endl;
}

void writeAlm(std::ofstream& salidaFile, const std::string& comentario, int valor) {
    salidaFile << comentario << std::endl;
    salidaFile << "ALM_NUM: " << valor << std::endl;
    salidaFile << "ALM_OUT: 0xF" << std::endl;
    salidaFile << "ALM_MASK: 0" << std::endl;
    salidaFile << "ALM_CHG: 0" << std::endl;
    salidaFile << "ALM_STATUS: 0x11" << std::endl;
    salidaFile << "ALM_SCNEW: begin" << std::endl;
    salidaFile << "\t\tinfo" << std::endl;
    salidaFile << "           end" << std::endl;
    salidaFile << "ALM_SCOLD: begin" << std::endl;
    salidaFile << "\t\tinfo" << std::endl;
    salidaFile << "           end" << std::endl;
    salidaFile << std::endl;
}

void writeNumCmds(std::ofstream& salidaFile, int valor) {
    salidaFile << "/* COMMANDES */\n" << std::endl;
    salidaFile << "NBR_CMD: " << valor << std::endl;
    salidaFile << std::endl;
}


void writeCmd(std::ofstream& salidaFile, const std::string& comentario, int valor) {
    salidaFile << comentario << std::endl;
    salidaFile << "CMD_NUM: " << valor << std::endl;
    salidaFile << "CMD_OUT: 0xF" << std::endl;
    salidaFile << "CMD_STATUS: 0x11" << std::endl;
    salidaFile << "CMD_SC:\tbegin" << std::endl;
    //salidaFile << "\t\t\t" << std::endl;
    salidaFile << "\tend" << std::endl;
    salidaFile << std::endl;	
    
}


void writeEnd(std::ofstream& salidaFile) {
	salidaFile << "DATE_SC: 	begin" << std::endl;
	salidaFile << "		end" << std::endl;
	salidaFile << "COUNTER_SC: 	begin" << std::endl;
	salidaFile << "		end"  << std::endl;
	salidaFile << "LOGIC_SC: 	begin" << std::endl;
	salidaFile << "		end"  << std::endl;
	salidaFile << "CNTADD_SC: 	begin" << std::endl;
	salidaFile << "		end"  << std::endl;
	salidaFile << "CNTADDF_SC: 	begin" << std::endl;
	salidaFile << "		end"  << std::endl;
	salidaFile << "MASKCMD0:	{" << std::endl;
	salidaFile << "		}" << std::endl;
	salidaFile << "MASKCMD1: 	{" << std::endl;
	salidaFile << "		}" << std::endl;
	salidaFile << "MASKCMD2: 	{" << std::endl;
	salidaFile << "		}" << std::endl;
    salidaFile << std::endl;	
						    
}

int main(int argc, char *argv[]) {// args [1] nom.txt [2]num_alms [3]num_cmds [4]space
    std::string fichier = "act.txt";
    int alms = 10; // Nombre d'alarmes créées
    int cmds = 10; // Nombre de cmd créés
    int space = 10; // Espace entre les alarmes et les commandes
    std::string comentario = "/**/"; // Récupère les commentaires du fichier de configuration cfg

	std::cout <<USAGE<<std::endl;
    // Analysez s'il y a des arguments
    if (argc < 5) {
        std::cerr << "Erreur args \n Example : makeAct nom_fichier alms cmds space " << std::endl;
        return 1;
    }

    fichier = argv[1]; // Nom fichier act

    try {
        alms = std::stoi(argv[2]); // num. alms
    } catch (const std::exception& e) {
        std::cerr << "Erreur num. alms : " << e.what() << std::endl;
        return 1;
    }

    try {
        cmds = std::stoi(argv[3]); // num. cmd
    } catch (const std::exception& e) {
        std::cerr << "Erreur num. cmds : " << e.what() << std::endl;
        return 1;
    }

    try {
        space = std::stoi(argv[4]); // spacement
    } catch (const std::exception& e) {
        std::cerr << "Erreur spacement : " << e.what() << std::endl;
        return 1;
    }

    std::ofstream salidaFile("act_" + fichier + ".txt"); // fichier avec act_
    if (!salidaFile) {
        std::cerr << "Erreur lors de la création du fichier de sortie." << std::endl;
        return 1;
    }

    // Write num.alms
    writeNumAlms(salidaFile, alms); // Write Num Alms Virtuelle

    // écrire des ALMs
    for (int alm = space; alm <= alms * space; alm += space) {
        writeAlm(salidaFile, comentario, alm);
    }

    // Write num. CMDs
    writeNumCmds(salidaFile, cmds); // Write Num Alms Virtuelle

    // écrire des commandes
    for (int cmd = space; cmd <= cmds * space; cmd += space) {
        writeCmd(salidaFile, comentario, cmd);
    }

    // écrire la dernière partie act
    writeEnd(salidaFile);

    std::cout << "Fichier de sortie créé avec succès." << std::endl;

    return 0;
}

