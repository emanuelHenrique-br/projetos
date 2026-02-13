package locadora;

import java.util.ArrayList;
import java.util.List;

public class Concessionaria {

	private String cnpj;
	private List<Carro> carros;

	public Concessionaria(String cnpj) {
		this.cnpj = cnpj;
		this.carros = new ArrayList<>();
	}

	private Carro buscarCarro(String placa) {
		for (Carro carro : carros) {
			if (carro.getPlaca().equalsIgnoreCase(placa)) {
				return carro;
			}
		}
		return null;
	}

	public void cadastrarCarro(String placa, String modelo, String cor, int anoFab, int quantidade, Double valor) {
		Carro existente = buscarCarro(placa);
		if (existente != null) {
			existente.adicionarCarroConcessionaria(quantidade);
			System.out.println("Carro já cadastrado! Quantidade atualizada.");
		} else {
			Carro cad = new Carro(placa, modelo, cor, anoFab, quantidade, valor);
			carros.add(cad);
			System.out.println("Carro cadastrado com sucesso!");
		}
	}

	public void removerCarro(String placa, int quantidade) {
		Carro existente = buscarCarro(placa);

		if (existente != null) {
			if (existente.getQuantidadeDisponivel() >= quantidade) {
				existente.removerCarroConcessionaria(quantidade);
				System.out.println("Quantidade removida com sucesso!");

				if (existente.getQuantidadeDisponivel() == 0) {
					carros.remove(existente);
					System.out.println("Estoque zerado. Modelo removido do catálogo.");
				}
			} else {
				System.out.println("Erro: Quantidade a remover maior que o estoque atual.");
			}
		} else {
			System.out.println("Erro: Carro com placa " + placa + " não encontrado no sistema.");
		}
	}

	public void adquirirCarro(String placa, int quantidade) {
		Carro carro = buscarCarro(placa);
		if (carro != null) {
			carro.adicionarCarroConcessionaria(quantidade);
			System.out.println("Carro adquirido (estoque reposto) com sucesso!");
		} else {
			System.out.println("Carro não encontrado para aquisição!");
		}
	}

	public void realizarVendaCarro(String placa, int quantidade) {
		Carro carro = buscarCarro(placa);
		if (carro != null) {
			if (carro.getQuantidadeDisponivel() >= quantidade) {
				carro.removerCarroConcessionaria(quantidade);
				System.out.printf("Venda realizada. Total: R$ %.2f\n", quantidade * carro.getValorVeiculo());

				if (carro.getQuantidadeDisponivel() == 0) {
					carros.remove(carro);
				}
			} else {
				System.out.println("Estoque insuficiente para realizar a venda.");
			}
		} else {
			System.out.println("Carro não encontrado!");
		}
	}

	public void exibirRelatorioCarros() {
		if (carros.isEmpty()) {
			System.out.println("Nenhum produto cadastrado.");
		} else {
			for (Carro carro : carros) {
				carro.exibirDados();
			}
		}
	}

	public String getCnpj() {
		return cnpj;
	}
}