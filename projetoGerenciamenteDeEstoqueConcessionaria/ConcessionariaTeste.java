package locadora;

public class ConcessionariaTeste {
    public static void main(String[] args) {

        Concessionaria concessionaria01 = new Concessionaria("12.345.678/0001-99");

        concessionaria01.cadastrarCarro("ABC-123", "FERRARI", "VERMELHO", 2020, 3, 980000.00);
        concessionaria01.removerCarro("ABC-123", 1); 
        concessionaria01.exibirRelatorioCarros();
    }
}