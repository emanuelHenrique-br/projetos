package locadora;

public class Carro {

	private String placa;
	private String modelo;
	private String cor;
	private int anoFabricacao;
	private int quantidadeDisponivel;
	private Double valorVeiculo;

	public Carro(String placa, String modelo, String cor, int anoFabricacao, int quantidadeDisponivel,
			Double valorVeiculo) {
		this.placa = placa;
		this.modelo = modelo;
		this.cor = cor;
		this.anoFabricacao = anoFabricacao;
		this.quantidadeDisponivel = quantidadeDisponivel;
		this.valorVeiculo = valorVeiculo;
	}

	public void adicionarCarroConcessionaria(int quantidade) {
		this.quantidadeDisponivel += quantidade;
	}

	public void removerCarroConcessionaria(int quantidade) {
		if (quantidade <= this.quantidadeDisponivel) {
			this.quantidadeDisponivel -= quantidade;
		} else {
			System.out.println("Erro: Não é possível remover mais carros do que o disponível.");
		}
	}

	public void exibirDados() {
		System.out.println("===============================================");
		System.out.println("Placa: " + placa);
		System.out.println("Modelo: " + modelo);
		System.out.println("Cor: " + cor);
		System.out.println("Ano: " + anoFabricacao);
		System.out.println("Quantidade Disponível: " + quantidadeDisponivel);
		System.out.printf("Valor Unitário: R$ %.2f\n", valorVeiculo);
		System.out.println("===============================================");
	}

	// Getters
	public String getPlaca() {
		return placa;
	}

	public int getQuantidadeDisponivel() {
		return quantidadeDisponivel;
	}

	public Double getValorVeiculo() {
		return valorVeiculo;
	}
}