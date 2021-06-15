#define VECTOR_MULTIPLY_DONT_INCLUDE_CFG_WORDS
#include "vector_multiply.h"
#undef VECTOR_MULTIPLY_DONT_INCLUDE_CFG_WORDS

extern unsigned short config_word_cmul_eq_0f [32];
extern unsigned short config_word_conj_eq_0f [32];


extern unsigned short config_word_add_eq_00 [32];

#include "xbaseband.h"


///
/// Multiply two 1024 vectors using data slice
/// @param is_conj is this argument
/// @input_data_fft input 1, row pointer
/// @input_data_nco input 2, row pointer
/// @output_data_location output , row pointer

void vector_multiply_1024(const unsigned int is_conj, const unsigned int input_data_fft, const unsigned int input_data_nco, const unsigned int output_data_location){
    if (is_conj == 0x1){
        MVXV_KNOP(V0, VMEM_ROW_ADDRESS(config_word_conj_eq_0f));
    } else {    
        MVXV_KNOP(V0, VMEM_ROW_ADDRESS(config_word_cmul_eq_0f));
    }
    
    VNOP_LK14(V0); //k14 configuration word
    MVXV_KNOP(V1, input_data_fft);
    MVXV_KNOP(V2, input_data_nco);
    MVXV_KNOP(V3, output_data_location);
    MVXV_KNOP(V4, 0x1);

    // for (unsigned int i = 0; i < 4; i++){
    //     ADD_LK8(V1, V1, V4, 0x0); 
    //     ADD_LK9(V2, V2, V4, 0x0);   
    // }

    // for (unsigned int i = 0; i < 12; i++){
    //     // VNOP_LK8(V1); // load k8 from memory
    //     // VNOP_LK9(V2); // load k9 from memory
    //     // VNOP_SK1(V3);
    //     ADD_LK8(V1, V1, V4, 0x0);
    //     ADD_LK9(V2, V2, V4, 0x0);
    //     ADD_SK1(V3, V3, V4, 0x0);
    // }

    for (unsigned int i = 0; i < 4; i++){
        // ADD_SK1(V3, V3, V4, 0x0);
        ADD_LK8(V1, V1, V4, 0x0);
        ADD_LK9(V2, V2, V4, 0x0);
    }

    for (unsigned int i = 0; i < 60; i++){
        ADD_LK8(V1, V1, V4, 0x0);
        ADD_LK9(V2, V2, V4, 0x0);
        ADD_SK1(V3, V3, V4, 0x0);
    }
    for (unsigned int i = 0; i < 4; i++){
        ADD_SK1(V3, V3, V4, 0x0);
    }
}

///
/// Multiply two 1024 vectors using data slice
/// @param is_conj is this argument
/// @input_data_fft input 1, row pointer
/// @input_data_nco input 2, row pointer
/// @output_data_location output , row pointer

void cfg_vector_multiply_1024(const unsigned int cfg_row, const unsigned int input_data_fft, const unsigned int input_data_nco, const unsigned int output_data_location) {
    MVXV_KNOP(V0, cfg_row);
    
    VNOP_LK14(V0); //k14 configuration word
    MVXV_KNOP(V1, input_data_fft);
    MVXV_KNOP(V2, input_data_nco);
    MVXV_KNOP(V3, output_data_location);
    MVXV_KNOP(V4, 0x1);


    for (unsigned int i = 0; i < 4; i++) {
        // ADD_SK1(V3, V3, V4, 0x0);
        ADD_LK8(V1, V1, V4, 0x0);
        ADD_LK9(V2, V2, V4, 0x0);
    }

    for (unsigned int i = 0; i < 60; i++) {
        ADD_LK8(V1, V1, V4, 0x0);
        ADD_LK9(V2, V2, V4, 0x0);
        ADD_SK1(V3, V3, V4, 0x0);
    }

    for (unsigned int i = 0; i < 4; i++) {
        ADD_SK1(V3, V3, V4, 0x0);
    }
}





void vector_add_1024(const unsigned int input_data_fft, const unsigned int input_data_nco, const unsigned int output_data_location){

    MVXV_KNOP(V0, VMEM_ROW_ADDRESS(config_word_add_eq_00));
    
    VNOP_LK14(V0); //k14 configuration word
    MVXV_KNOP(V1, input_data_fft);
    MVXV_KNOP(V2, input_data_nco);
    MVXV_KNOP(V3, output_data_location);
    MVXV_KNOP(V4, 0x1);

    // for (unsigned int i = 0; i < 4; i++){
    //     ADD_LK8(V1, V1, V4, 0x0); 
    //     ADD_LK9(V2, V2, V4, 0x0);   
    // }

    // for (unsigned int i = 0; i < 12; i++){
    //     // VNOP_LK8(V1); // load k8 from memory
    //     // VNOP_LK9(V2); // load k9 from memory
    //     // VNOP_SK1(V3);
    //     ADD_LK8(V1, V1, V4, 0x0);
    //     ADD_LK9(V2, V2, V4, 0x0);
    //     ADD_SK1(V3, V3, V4, 0x0);
    // }

    for (unsigned int i = 0; i < 4; i++){
        // ADD_SK1(V3, V3, V4, 0x0);
        ADD_LK8(V1, V1, V4, 0x0);
        ADD_LK9(V2, V2, V4, 0x0);
    }

    for (unsigned int i = 0; i < 60; i++){
        ADD_LK8(V1, V1, V4, 0x0);
        ADD_LK9(V2, V2, V4, 0x0);
        ADD_SK1(V3, V3, V4, 0x0);
    }
    for (unsigned int i = 0; i < 4; i++){
        ADD_SK1(V3, V3, V4, 0x0);
    }

}

