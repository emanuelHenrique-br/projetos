const bancoDeDados = {
    "rolante": {
        cidade: "Rolante, BR",
        temp: "27,3",
        condicao: "Nublado",
        tempMax: "27,3",
        tempMin: "27,3",
        umidade: "52",
        vento: "1.4",
        icone: "nuvem"
    },
    "sao paulo": {
        cidade: "São Paulo, SP",
        temp: "19,0",
        condicao: "Chuvoso",
        tempMax: "22,0",
        tempMin: "18,0",
        umidade: "85",
        vento: "12.0",
        icone: "chuva"
    },
    "rio de janeiro": {
        cidade: "Rio de Janeiro, RJ",
        temp: "35,0",
        condicao: "Ensolarado",
        tempMax: "38,0",
        tempMin: "24,0",
        umidade: "40",
        vento: "5.5",
        icone: "sol"
    },
    "curitiba": {
        cidade: "Curitiba, PR",
        temp: "12,0",
        condicao: "Nublado",
        tempMax: "15,0",
        tempMin: "8,0",
        umidade: "60",
        vento: "10.0",
        icone: "nuvem"
    },
    "salvador": {
        cidade: "Salvador, BA",
        temp: "30,0",
        condicao: "Parc. Nublado",
        tempMax: "31,0",
        tempMin: "25,0",
        umidade: "70",
        vento: "15.0",
        icone: "sol-nuvem"
    }
};

const cityInput = document.getElementById("city-input");
const searchBtn = document.getElementById("search-btn");

const cityElement = document.getElementById("city");
const tempElement = document.getElementById("temperature");
const descElement = document.getElementById("description");
const weatherIconElement = document.getElementById("weather-icon");
const tempMaxElement = document.getElementById("temp-max");
const tempMinElement = document.getElementById("temp-min");
const humidityElement = document.getElementById("humidity");
const windElement = document.getElementById("wind");

function formatarTexto(texto) {
    return texto
        .toLowerCase()
        .normalize('NFD')
        .replace(/[\u0300-\u036f]/g, "")
        .trim();
}

function buscarCidade(nomeCidade) {
    const chave = formatarTexto(nomeCidade);
    const dados = bancoDeDados[chave];

    if (dados) {
        atualizarTela(dados);
    } else {
        alert("Cidade não encontrada no banco de dados simulado!\nTente: Rolante, São Paulo, Rio de Janeiro, Curitiba ou Salvador.");
    }
}

function atualizarTela(dados) {
    cityElement.innerText = dados.cidade;
    tempElement.innerText = dados.temp;
    descElement.innerText = dados.condicao;
    
    tempMaxElement.innerText = `${dados.tempMax} °C`;
    tempMinElement.innerText = `${dados.tempMin} °C`;
    humidityElement.innerText = `${dados.umidade}%`;
    windElement.innerText = `${dados.vento} km/h`;

    atualizarIcone(dados.icone);
}

function atualizarIcone(tipo) {

    weatherIconElement.className = "fa-solid weather-icon";

    if (tipo === "sol") {
        weatherIconElement.classList.add("fa-sun");
    } else if (tipo === "nuvem") {
        weatherIconElement.classList.add("fa-cloud");
    } else if (tipo === "chuva") {
        weatherIconElement.classList.add("fa-cloud-rain");
    } else if (tipo === "sol-nuvem") {
        weatherIconElement.classList.add("fa-cloud-sun");
    } else {
        weatherIconElement.classList.add("fa-cloud");
    }
}

searchBtn.addEventListener("click", () => {
    const cidade = cityInput.value;
    if(cidade) buscarCidade(cidade);
});

cityInput.addEventListener("keyup", (e) => {
    if (e.code === "Enter") {
        const cidade = e.target.value;
        if(cidade) buscarCidade(cidade);
    }
});

buscarCidade("Rolante");