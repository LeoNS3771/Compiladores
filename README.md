Implementações de hoje:

- Funções
USO: 
    fun nomeFuncao(atributo : tipo) : tipoRetorno
    {   
        fun fazAlgo() : void -> não verifiquei o uso de uma função do tipo void atribuida a uma variavel :(
        {
            out("fiz Algo")
        }
        fazAlgo(); 

        return tipoRetorno;   
    }

- Struct <--- Falta acessar objeto struct pelo lado direito e pelo lado esquerda
USO:
    Ponto {
        x : float;
        y : float;
    };

        p : Ponto = {10, 20}; 
    OU
        p : Ponto;
        p.x = 10;
        p.y = 20;

    out(p.x, p.y);

- import <----- Joga tudo que tiver no arquivo <nome.sk> em cima do programa.sk
USO:
    import <vetor.sk> <--- vai jogar todo o arquivo