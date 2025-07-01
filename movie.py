import random
import os

# Gêneros disponíveis
generos = ["Ação", "Comédia", "Romance", "Drama", "Ficção Científica", "Terror", "Suspense", "Fantasia"]

# Exemplo de base de filmes (serão gerados aleatoriamente)
filmes_base = [
    "O Cavaleiro das Trevas", "Pulp Fiction", "Interestelar", "Clube da Luta", "Toy Story",
    "A Origem", "O Senhor dos Anéis", "Coringa", "Matrix", "Os Incríveis",
    "O Iluminado", "De Repente 30", "Diário de uma Paixão", "Psicose", "Os Caça-Fantasmas",
    "O Silêncio dos Inocentes", "Forrest Gump", "Harry Potter", "A Vida é Bela", "O Exterminador do Futuro"
]

print("Quantos Filmes Deseja Gerar?")
qtd = int(input())

# Gerar 1000 filmes aleatórios
with open("movies.txt", "w", encoding="utf-8") as file:
    for i in range(qtd):
        titulo = random.choice(filmes_base) + f" {random.randint(1, 5)}"  # Título + número para variar
        ano = random.randint(1970, 2023)
        nota = round(random.uniform(5.0, 9.9), 1)
        genero = random.choice(generos)
        file.write(f"{titulo};{ano};{nota};{genero}\n")

print("Arquivo 'movies.txt' gerado com sucesso!")