import pygame

class Jogador:
    def __init__(self, largura, altura):

        self.escala = altura / 600

        largura_jogador = int(100 * self.escala)
        altura_jogador = int(32 * self.escala)

        imagem_original = pygame.image.load("assets/cesto.png")
        self.imagem = pygame.transform.smoothscale(imagem_original,(largura_jogador, altura_jogador))

        self.rect = pygame.Rect(0, 0, largura_jogador, altura_jogador)

        self.rect.centerx = largura // 2
        self.rect.bottom = altura - int(20 * self.escala)

        self.velocidade = 6 * (self.escala ** 1.3)

    def mover(self, teclas, largura):

        if teclas[pygame.K_LEFT] or teclas[pygame.K_a]:
            self.rect.x -= self.velocidade

        if teclas[pygame.K_RIGHT] or teclas[pygame.K_d]:
            self.rect.x += self.velocidade

        if self.rect.left < 0:
            self.rect.left = 0

        if self.rect.right > largura:
            self.rect.right = largura

    def desenhar(self, ecra):
        ecra.blit(self.imagem, self.rect)

