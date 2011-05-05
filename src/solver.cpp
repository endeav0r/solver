#include "solver.hpp"
#include <cstdlib>
#include <ctime>


Operation * Solver :: get_operation (std::string name) {
    std::list <Operation *> :: iterator it;
    
    for (it = this->operations.begin(); it != this->operations.end(); it++) {
        if ((*it)->g_name() == name)
            return *it;
    }
    return NULL;
}


Word Solver :: find_best_M (std::string operation_name, int M_index) {
    Operation * operation;
    Add * adder;
    Word result;
    
    operation = get_operation(operation_name);
    adder = dynamic_cast<Add *>(operation);
    
    result = adder->best_adder(M[M_index]->g_name());

    return result;
}


void Solver :: find_best_Ms () {
    bool unset[16];
    int i;
    
    for (i = 0; i < 16; i++) {
        M[i]->s_word(rand());
        M[i]->s_mask(0xffffffff);
        unset[i] = false;
    }
    /*
    i = 0;
    while (i < 4) {
        selection = rand() % 16;
        if (unset[selection] == false) {
            unset[selection] = true;
            i++;
            M[selection]->s_mask(0x00000000);
        }
    }
    */
    M[8]->s_mask(0x00000000);
    M[9]->s_mask(0x00000000);
    M[12]->s_mask(0x00000000);
    M[13]->s_mask(0x00000000);
    /*
    M[ 4]->take_bits(find_best_M("step_sum_op__18", 4));
    M[ 8]->take_bits(find_best_M("step_sum_op__19", 8));
    M[12]->take_bits(find_best_M("step_sum_op__20", 12));
    M[ 1]->take_bits(find_best_M("step_sum_op__21", 1));
    M[ 5]->take_bits(find_best_M("step_sum_op__22", 5));
    M[ 9]->take_bits(find_best_M("step_sum_op__23", 9));
    M[13]->take_bits(find_best_M("step_sum_op__24", 13));
    std::cout << "best M" << 13 << " " << M[13]->bit_string() << "\n";
    */
}


void Solver :: md4F (Word * a, Word * b, Word * c, Word * d,
                     Word * M, Word * r, int step, int bits) {
    
    std::stringstream s;
    s << step;
    
    Not  * b_not_op     = new Not( std::string("b_not_op_____") + s.str());
    And  * f_left_op    = new And (std::string("f_left_op____") + s.str());
    And  * f_right_op   = new And (std::string("f_right_op___") + s.str());
    Or   * f_op         = new Or  (std::string("f_op_________") + s.str());
    Add  * step_sum_op  = new Add (std::string("step_sum_op__") + s.str());
    Rotl * step_rotl_op = new Rotl(std::string("step_rotl_op_") + s.str());
    
    Word * b_not    = new Word(std::string("b_not____") + s.str());
    Word * f_left   = new Word(std::string("f_left___") + s.str());
    Word * f_right  = new Word(std::string("f_right__") + s.str());
    Word * f        = new Word(std::string("f________") + s.str());
    Word * step_sum = new Word(std::string("step_sum_") + s.str());
    
    b_not_op->s_result(b_not);
    f_left_op->s_result(f_left);
    f_right_op->s_result(f_right);
    f_op->s_result(f);
    step_sum_op->s_result(step_sum);
    step_rotl_op->s_result(r);
    
    step_rotl_op->s_source(step_sum);
    step_rotl_op->s_bits(bits);
    
    b_not_op->s_source(b);
    
    f_left_op->add_operand(b);
    f_left_op->add_operand(c);
    
    f_right_op->add_operand(b_not);
    f_right_op->add_operand(d);
    
    f_op->add_operand(f_left);
    f_op->add_operand(f_right);
    
    step_sum_op->add_operand(a);
    step_sum_op->add_operand(f);
    step_sum_op->add_operand(M);
    
    this->op_words.push_back(b_not);
    this->op_words.push_back(f_left);
    this->op_words.push_back(f_right);
    this->op_words.push_back(f);
    this->op_words.push_back(step_sum);
    
    this->operations.push_back(b_not_op);
    this->operations.push_back(f_left_op);
    this->operations.push_back(f_right_op);
    this->operations.push_back(f_op);
    this->operations.push_back(step_sum_op);
    this->operations.push_back(step_rotl_op);

}


void Solver :: md4G (Word * a, Word * b, Word * c, Word * d,
                     Word * M, Word * r, int step, int bits) {
    
    std::stringstream s;
    s << step;

    And  * g_left_op    = new And (std::string("g_left_op____") + s.str());
    And  * g_middle_op  = new And (std::string("g_middle_op__") + s.str());
    And  * g_right_op   = new And (std::string("g_right_op___") + s.str());
    Or   * g_op         = new Or  (std::string("g_op_________") + s.str());
    Add  * step_sum_op  = new Add (std::string("step_sum_op__") + s.str());
    Rotl * step_rotl_op = new Rotl(std::string("step_rotl_op_") + s.str());
    
    Word * g_left   = new Word(std::string("g_left___") + s.str());
    Word * g_middle = new Word(std::string("g_middle_") + s.str());
    Word * g_right  = new Word(std::string("g_right__") + s.str());
    Word * g        = new Word(std::string("g________") + s.str());
    Word * step_sum = new Word(std::string("step_sum_") + s.str());
    
    g_left_op->s_result(g_left);
    g_middle_op->s_result(g_middle);
    g_right_op->s_result(g_right);
    
    g_op->s_result(g);
    step_sum_op->s_result(step_sum);
    step_rotl_op->s_result(r);
    
    step_rotl_op->s_source(step_sum);
    step_rotl_op->s_bits(bits);
    
    g_left_op->add_operand(b);
    g_left_op->add_operand(c);
    
    g_middle_op->add_operand(b);
    g_middle_op->add_operand(d);
    
    g_right_op->add_operand(c);
    g_right_op->add_operand(d);
    
    g_op->add_operand(g_left);
    g_op->add_operand(g_middle);
    g_op->add_operand(g_right);
    
    step_sum_op->add_operand(a);
    step_sum_op->add_operand(g);
    step_sum_op->add_operand(M);
    step_sum_op->add_operand(GConstant);
    
    this->op_words.push_back(g_left);
    this->op_words.push_back(g_right);
    this->op_words.push_back(g_middle);
    this->op_words.push_back(g);
    this->op_words.push_back(step_sum);
    
    this->operations.push_back(g_left_op);
    this->operations.push_back(g_middle_op);
    this->operations.push_back(g_right_op);
    this->operations.push_back(g_op);
    this->operations.push_back(step_sum_op);
    this->operations.push_back(step_rotl_op);

}


void Solver :: md4H (Word * a, Word * b, Word * c, Word * d,
                     Word * M, Word * r, int step, int bits) {
    
    std::stringstream s;
    s << step;
    
    Xor  * h_op         = new Xor (std::string("g_op_________") + s.str());
    Add  * step_sum_op  = new Add (std::string("step_sum_op__") + s.str());
    Rotl * step_rotl_op = new Rotl(std::string("step_rotl_op_") + s.str());
    
    Word * h        = new Word(std::string("g________") + s.str());
    Word * step_sum = new Word(std::string("step_sum_") + s.str());
        
    h_op->s_result(h);
    step_sum_op->s_result(step_sum);
    step_rotl_op->s_result(r);
    
    step_rotl_op->s_source(step_sum);
    step_rotl_op->s_bits(bits);
    
    h_op->add_operand(b);
    h_op->add_operand(c);
    h_op->add_operand(d);
    
    step_sum_op->add_operand(a);
    step_sum_op->add_operand(h);
    step_sum_op->add_operand(M);
    step_sum_op->add_operand(HConstant);
    
    this->op_words.push_back(h);
    this->op_words.push_back(step_sum);
    
    this->operations.push_back(h_op);
    this->operations.push_back(step_sum_op);
    this->operations.push_back(step_rotl_op);

}


bool Solver :: validate () {
    if (   (a[0]->g_word() == 0x01234567)
        && (b[0]->g_word() == 0x89abcdef)
        && (c[0]->g_word() == 0x76543210)
        && (d[0]->g_word() == 0xfedcba98)
        && (a[8]->g_word() == 0xAAAAAAAA)
        && (b[8]->g_word() == 0xAAAAAAAA)
        && (c[8]->g_word() == 0xAAAAAAAA)
        && (d[8]->g_word() == 0xAAAAAAAA)
        && (GConstant->g_word() == 0x5a827999))
        return true;
    return false;
}

void Solver :: execute () {
    std::list <Operation *> :: iterator it;
    std::stringstream debug_steps;
    bool change = true;
    
    while (change) {
        change = false;
        for (it  = this->operations.begin();
             it != this->operations.end();
             it++) {
            if ((*it)->execute()) {
                debug_steps << "[*] " << (*it)->g_name() << "\n";
                if (validate() == false) {
                    std::cout << debug_steps.str();
                    output_state();
                    throw -1;
                }
                change = true;
            }
            else {
                debug_steps << "[ ] " << (*it)->g_name() << "\n";
                if (validate() == false) {
                    std::cout << debug_steps.str();
                    output_state();
                    throw -1;
                }
            }
        }
    }
}


int Solver :: bit_count () {
    int i;
    int bit_count = 0;
    std::list <Word *> :: iterator it;

    for (i = 0; i < 16; i++) {
        bit_count += M[i]->mask_count();
    }
    
    for (i = 0; i < 9; i++) {
        bit_count += a[i]->mask_count() + b[i]->mask_count();
        bit_count += c[i]->mask_count() + d[i]->mask_count();
    }
    
    for (it = this->op_words.begin(); it != this->op_words.end(); it++) {
        bit_count += (*it)->mask_count();
    }
    
    return bit_count;
    
}


void Solver :: output_state () {
    int i;
    std::list <Word *> :: iterator it;

    std::cout << "GConstant " << GConstant->bit_string() << "\n";

    for (i = 0; i < 16; i++) {
        std::cout << "M[" << i << "] " << M[i]->bit_string() << "\n";
    }
    
    for (i = 0; i < 13; i++) {
        std::cout << "a[" << i << "] " << a[i]->bit_string() << "\n";
        std::cout << "b[" << i << "] " << b[i]->bit_string() << "\n";
        std::cout << "c[" << i << "] " << c[i]->bit_string() << "\n";
        std::cout << "d[" << i << "] " << d[i]->bit_string() << "\n";
    }
    

    for (it = this->op_words.begin(); it != this->op_words.end(); it++) {
        std::cout << (*it)->g_name() << " " << (*it)->bit_string() << "\n";
    }
    
    std::cout << "bit_count: " << bit_count() << "\n";

}


void Solver :: initialize_values () {
    int i;
    std::list <Word *> :: iterator it;
    
    for (it = this->op_words.begin(); it != this->op_words.end(); it++) {
        (*it)->s_mask(0x00000000);
        (*it)->s_word(0x00000000);
    }
    
    GConstant->s_word(0x5a827999);
    GConstant->s_mask(0xffffffff);
    HConstant->s_word(0x6ed9eba1);
    HConstant->s_mask(0xffffffff);
    
    for (i = 0; i < 16; i++) {
        M[i]->s_word(0x00000000);
        M[i]->s_mask(0xffffffff);
    }
    
    for (i = 0; i < 13; i++) {
        a[i]->s_word(0x00000000);
        b[i]->s_word(0x00000000);
        c[i]->s_word(0x00000000);
        d[i]->s_word(0x00000000);
        a[i]->s_mask(0x00000000);
        b[i]->s_mask(0x00000000);
        c[i]->s_mask(0x00000000);
        d[i]->s_mask(0x00000000);
    }
    
    /*M[0]->s_word(0xdeadbeef);
    M[1]->s_word(0xbeefdead);
    M[2]->s_word(0xdaedfeeb);
    M[3]->s_word(0xfeebdaed);
    */
    a[0]->s_word(0x01234567);
    b[0]->s_word(0x89abcdef);
    c[0]->s_word(0x76543210);
    d[0]->s_word(0xfedcba98);
    a[0]->s_mask(0xffffffff);
    b[0]->s_mask(0xffffffff);
    c[0]->s_mask(0xffffffff);
    d[0]->s_mask(0xffffffff);
    
    a[8]->s_word(0xAAAAAAAA);
    b[8]->s_word(0xAAAAAAAA);
    c[8]->s_word(0xAAAAAAAA);
    d[8]->s_word(0xAAAAAAAA);
    a[8]->s_mask(0xffffffff);
    b[8]->s_mask(0xffffffff);
    c[8]->s_mask(0xffffffff);
    d[8]->s_mask(0xffffffff);
}

Solver :: Solver () {
    int i, j;
    std::stringstream s;
    
    srand(time(NULL));
    
    GConstant = new Word (0x5a827999, 0xffffffff);
    HConstant = new Word (0x6ed9eba1, 0xffffffff);
    
    for (i = 0; i < 16; i++) {
        M[i] = new Word (0x00000000, 0xffffffff);
    }

    for (i = 0; i < 13; i++) {
        s.str("");
        s << "a" << i;
        a[i] = new Word(s.str());
        s.str("");
        s << "b" << i;
        b[i] = new Word(s.str());
        s.str("");
        s << "c" << i;
        c[i] = new Word(s.str());
        s.str("");
        s << "d" << i;
        d[i] = new Word(s.str());
    }
    
    for (i = 0; i < 4; i++) {
        j = i * 4;
        md4F(a[i], b[i  ], c[i  ], d[i  ], M[j  ], a[i+1], j+1, 3);
        md4F(d[i], a[i+1], b[i  ], c[i  ], M[j+1], d[i+1], j+2, 7);
        md4F(c[i], d[i+1], a[i+1], b[i  ], M[j+2], c[i+1], j+3, 11);
        md4F(b[i], c[i+1], d[i+1], a[i+1], M[j+3], b[i+1], j+4, 19);
    }
    
    i = 4;
    md4G(a[4], b[4], c[4], d[4], M[ 0], a[5], 17, 3);
    md4G(d[4], a[5], b[4], c[4], M[ 4], d[5], 18, 5);
    md4G(c[4], d[5], a[5], b[4], M[ 8], c[5], 19, 9);
    md4G(b[4], c[5], d[5], a[5], M[12], b[5], 20, 13);
    
    i = 5;
    md4G(a[i], b[i  ], c[i  ], d[i  ], M[ 1], a[i+1], 21, 3);
    md4G(d[i], a[i+1], b[i  ], c[i  ], M[ 5], d[i+1], 22, 5);
    md4G(c[i], d[i+1], a[i+1], b[i  ], M[ 9], c[i+1], 23, 9);
    md4G(b[i], c[i+1], d[i+1], a[i+1], M[13], b[i+1], 24, 13);
    
    i = 6;
    md4G(a[i], b[i  ], c[i  ], d[i  ], M[ 2], a[i+1], 25, 3);
    md4G(d[i], a[i+1], b[i  ], c[i  ], M[ 6], d[i+1], 26, 5);
    md4G(c[i], d[i+1], a[i+1], b[i  ], M[10], c[i+1], 27, 9);
    md4G(b[i], c[i+1], d[i+1], a[i+1], M[14], b[i+1], 28, 13);
    
    i = 7;
    md4G(a[i], b[i  ], c[i  ], d[i  ], M[ 3], a[i+1], 29, 3);
    md4G(d[i], a[i+1], b[i  ], c[i  ], M[ 7], d[i+1], 30, 5);
    md4G(c[i], d[i+1], a[i+1], b[i  ], M[11], c[i+1], 31, 9);
    md4G(b[i], c[i+1], d[i+1], a[i+1], M[15], b[i+1], 32, 13);

    int highest_bit_count = 0;
    int bc;
    for (int i = 0; i < 600000; i++) {
        initialize_values();
        find_best_Ms();
        execute();
        bc = 0;
        for (j = 0; j < 16; j++) {
            bc += M[j]->mask_count();
        }
        if (bc > 32 * 12) {
            output_state();
            std::cout << "FOUND M\n";
        }
        if (bit_count() > highest_bit_count) {
            highest_bit_count = bit_count();
            output_state();
        }
        std::cout.flush();
    }
    
}

    
Solver :: ~Solver () {
    for (int i = 0; i < 13; i++) {
        delete a[i];
        delete b[i];
        delete c[i];
        delete d[i];
    }
    for (int i = 0; i < 16; i++) {
        delete M[i];
    }
}


int main () {
    Solver solver;
    return 0;
}
