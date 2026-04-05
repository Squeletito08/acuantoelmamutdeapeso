// Generador de números aleatorio extremadamente rápido con periodo de 64 bits
// y con propiedades estadísticas excelentes. Probablemente sea más adecuado
// en cualquier contexto que mt19937.
struct pcg32
{
    using result_type = unsigned int; // se debe llamar result_type para std
    unsigned long long state, inc;
    static constexpr result_type min() { return 0; } // es sólo para std
    static constexpr result_type max() { return ~0u; } // es sólo para std
    pcg32() : state(0x853c49e6748fea9bULL), inc(0xda3e39cb94b95bdbULL) {}
    result_type operator()() {
        auto old = state;
        state = old * 6364136223846793005ULL + (inc|1);
        result_type xsh = ((old >> 18u) ^ old) >> 27u;
        result_type rot = old >> 59u;
        return (xsh >> rot) | (xsh << ((-rot) & 31));
    }
};
