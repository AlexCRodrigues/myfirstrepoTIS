import pygame
import random

class Fruta:
    def __init__(self, largura, altura):

        self.largura_ecra = largura
        self.altura_ecra = altura

        self.escala = altura / 600
        tamanho = max(1, int(20 * self.escala))

        imagem_original = pygame.image.load("assets/maca.png")
        self.imagem = pygame.transform.smoothscale(
            imagem_original,
            (tamanho, tamanho)
        )

        self.ultima_posicao_x = None

        self.rect = pygame.Rect(
            random.randint(0, largura - tamanho),
            random.randint(int(-150 * self.escala), int(-40 * self.escala)),
            tamanho,
            tamanho
        )

        self.ultima_posicao_x = self.rect.x
        self.posicao_y = float(self.rect.y)
        self.velocidade = 4 * (self.escala ** 1.3)

    def atualizar(self):
        self.posicao_y += self.velocidade
        self.rect.y = int(self.posicao_y)

    def reposicionar(self):

        distancia_minima = int(150 * self.escala)

        nova_x = random.randint(0, self.largura_ecra - self.rect.width)

        tentativas = 0

        while abs(nova_x - self.ultima_posicao_x) < distancia_minima and tentativas < 100:
            nova_x = random.randint(0, self.largura_ecra - self.rect.width)
            tentativas += 1

        self.rect.x = nova_x
        self.ultima_posicao_x = nova_x

        self.rect.y = random.randint(
            int(-150 * self.escala),
            int(-40 * self.escala)
        )

        self.posicao_y = float(self.rect.y)

    def desenhar(self, ecra):
        ecra.blit(self.imagem, self.rect)
