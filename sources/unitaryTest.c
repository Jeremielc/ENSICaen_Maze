#include "mainHeader.h"
#include "CUnit/Basic.h"

void verifyFormatName();

int main(int argc, char** argv) {
    CU_pSuite pSuite[5] = {};

    CU_initialize_registry();

    pSuite[0] = CU_add_suite("Verify formatName()", NULL, NULL);
    CU_ADD_TEST(pSuite[0], verifyFormatName);

    /*pSuite[1] = CU_add_suite("Vérification copie de chaine", init_verifierCopie, clean_verifierCopie);
    CU_ADD_TEST(pSuite[1], test_verifierCopieIndice ) ;*/

    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

void verifyFormatName() {   /*Verify that spaces in the name are replaced by underscores.*/
    char* name = "grille 1";
    char* wellFormatedName = formatName(name);
    CU_ASSERT(strcmp(wellFormatedName, "grille_1") == 0);

    name = "special ! ? ; :";
    wellFormatedName = formatName(name);
    CU_ASSERT(strcmp(wellFormatedName, "special_!_?_;_:") == 0);

    name = NULL;
    wellFormatedName = formatName(NULL);
    CU_ASSERT(wellFormatedName == NULL);
}
