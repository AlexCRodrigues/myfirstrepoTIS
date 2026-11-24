import pygame
import random
from jogador import Jogador
from fruta import Fruta

pygame.init()

LARGURA, ALTURA = 1000, 800
ecra = pygame.display.set_mode((LARGURA, ALTURA))
pygame.display.set_caption("Apanha-Fruta")
relogio = pygame.time.Clock()
fonte = pygame.font.SysFont(None, 36)
fonte_grande = pygame.font.SysFont(None, 65)
fonte_pequena = pygame.font.SysFont(None, 28)
fundo_original = pygame.image.load("assets/background.png")
fundo = pygame.transform.smoothscale(fundo_original, (LARGURA, ALTURA))


class Jogo:

    def __init__(self):
        self.pontos = 0
        self.vidas = 3
        self.recorde = 0
        self.fim_de_jogo = False
        self.estado = "inicio"

        self.jogador = Jogador(LARGURA, ALTURA)
        self.frutas = [Fruta(LARGURA, ALTURA) for i in range(2)]

        self.reposicionar_fruta(self.frutas[1])

    def reposicionar_fruta(self, fruta):

        outra_fruta = next(f for f in self.frutas if f != fruta)

        distancia_maxima = LARGURA * 0.5

        tentativas = 0

        while tentativas < 1000:

            nova_x = random.randint(
                0,
                LARGURA - fruta.rect.width
            )

            distancia = abs(
                (nova_x + fruta.rect.width // 2) -
                outra_fruta.rect.centerx
            )

            if distancia <= distancia_maxima:
                break

            tentativas += 1

        fruta.rect.x = nova_x
        fruta.ultima_posicao_x = nova_x

        fruta.rect.y = random.randint(
            int(-150 * fruta.escala),
            int(-40 * fruta.escala)
        )

        fruta.posicao_y = float(fruta.rect.y)

    def desenhar_texto_centrado(self, texto, fonte, cor, y):

        superficie = fonte.render(texto, True, cor)
        retangulo = superficie.get_rect(center=(ecra.get_width() // 2, y))

        ecra.blit(superficie, retangulo)

    def apanhar_fruta(self, fruta):

        self.pontos += 1

        if self.pontos > self.recorde:
            self.recorde = self.pontos

        velocidade = (4 + (self.pontos // 10)) * (ALTURA / 600)

        for f in self.frutas:
            f.velocidade = velocidade

        self.reposicionar_fruta(fruta)

    def perder_vida(self, fruta):

        self.vidas -= 1
        self.reposicionar_fruta(fruta)

        if self.vidas <= 0:
            self.fim_de_jogo = True
            self.estado = "fim"

    def reiniciar(self):

        self.pontos = 0
        self.vidas = 3
        self.fim_de_jogo = False

        self.jogador = Jogador(LARGURA, ALTURA)
        self.frutas = [Fruta(LARGURA, ALTURA) for i in range(2)]

        self.reposicionar_fruta(self.frutas[1])

        self.estado = "jogar"

    def desenhar_vidas(self):

        for i in range(self.vidas):
            x = LARGURA - 80 + (i * 25)
            y = 25

            pygame.draw.circle(ecra, (255, 50, 70), (x - 5, y), 7)
            pygame.draw.circle(ecra, (255, 50, 70), (x + 5, y), 7)

            pygame.draw.polygon(ecra, (255, 50, 70), [
                (x - 12, y + 3),
                (x + 12, y + 3),
                (x, y + 17)
            ])

    def desenhar_inicio(self):

        self.desenhar_texto_centrado(
            "APANHA-FRUTA", fonte_grande,
            (255, 200, 50), ALTURA // 2 - 200
        )

        instrucoes = [
            "Apanha as frutas com o cesto!",
            "Setas ou A/D para movimentar",
            "Cada fruta apanhada vale 1 ponto",
            "Cada fruta perdida retira uma vida",
            "Tens 3 vidas!",
            "",
            "Carrega em ESPACO para comecar"
        ]

        for i, linha in enumerate(instrucoes):

            y = ALTURA // 2 - 80 + i * 38

            self.desenhar_texto_centrado(
                linha, fonte_pequena, (255, 255, 255), y
            )

    def desenhar_fim(self):

        self.desenhar_texto_centrado(
            "FIM DE JOGO", fonte_grande,
            (255, 50, 50), ALTURA // 2 - 120
        )

        self.desenhar_texto_centrado(
            f"Pontuacao final: {self.pontos}",
            fonte, (255, 255, 255), ALTURA // 2 - 40
        )

        self.desenhar_texto_centrado(
            f"Recorde: {self.recorde}",
            fonte, (255, 200, 50), ALTURA // 2 + 10
        )

        self.desenhar_texto_centrado(
            "Carrega em R para recomecar",
            fonte_pequena, (255, 255, 255), ALTURA // 2 + 90
        )

    def atualizar(self):

        teclas = pygame.key.get_pressed()

        self.jogador.mover(teclas, LARGURA)

        for fruta in self.frutas:

            fruta.atualizar()

            if self.jogador.rect.colliderect(fruta.rect):
                self.apanhar_fruta(fruta)

            elif fruta.rect.top > ALTURA:
                self.perder_vida(fruta)

                if self.fim_de_jogo:
                    break

    def desenhar_jogo(self):

        self.jogador.desenhar(ecra)

        for fruta in self.frutas:
            fruta.desenhar(ecra)

        texto = fonte.render(
            f"Pontos: {self.pontos}   Recorde: {self.recorde}",
            True, (255, 255, 255)
        )

        ecra.blit(texto, (10, 10))
        self.desenhar_vidas()

    def eventos(self):

        for evento in pygame.event.get():

            if evento.type == pygame.QUIT:
                return False

            if evento.type == pygame.KEYDOWN:

                if evento.key == pygame.K_ESCAPE:
                    return False

                if self.estado == "inicio":
                    if evento.key == pygame.K_SPACE:
                        self.estado = "jogar"

                elif self.estado == "fim":
                    if evento.key == pygame.K_r:
                        self.reiniciar()

        return True

    def executar(self):

        a_correr = True

        while a_correr:

            a_correr = self.eventos()

            if self.estado == "jogar":
                self.atualizar()

            ecra.blit(fundo, (0, 0))

            if self.estado == "inicio":
                self.desenhar_inicio()

            elif self.estado == "jogar":
                self.desenhar_jogo()

            elif self.estado == "fim":
                self.desenhar_fim()

            pygame.display.flip()
            relogio.tick(60)

jogo = Jogo()
jogo.executar()

pygame.quit()
