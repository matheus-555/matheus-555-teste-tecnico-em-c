#include "unity/unity.h"
#include "../inc/funcionario.h"

#define QTDE_FUNCIONARIO 5

// config inicial
void setUp()
{
}

// clear
void tearDown()
{
}

void teste_cadastro_dinamico_funcionario()
{
    // -------------------------------------
    //   CADASTRO
    // -------------------------------------
    funcionario_t **f = malloc(QTDE_FUNCIONARIO * sizeof(funcionario_t *));
    f[0] = funcionario_init_dinamico(FUNCIONARIO_CONTRATO_TERCEIRIZADO, (funcionario_tipo_contrato_t){.terceirizado = {.valor_por_hora = 50, .horas_trabalhadas = 100}}, "Joao", 0, 0);
    f[1] = funcionario_init_dinamico(FUNCIONARIO_CONTRATO_CLT, (funcionario_tipo_contrato_t){.clt = {.salario = 3000}}, "Marcela", 10, 200);
    f[2] = funcionario_init_dinamico(FUNCIONARIO_CONTRATO_TERCEIRIZADO, (funcionario_tipo_contrato_t){.terceirizado = {.valor_por_hora = 30, .horas_trabalhadas = 180}}, "Joaquim", 12, 200);
    f[3] = funcionario_init_dinamico(FUNCIONARIO_CONTRATO_CLT, (funcionario_tipo_contrato_t){.terceirizado = {.valor_por_hora = 10, .horas_trabalhadas = 5}}, "Matheus", 5, 6);
    f[4] = funcionario_init_dinamico(FUNCIONARIO_CONTRATO_TERCEIRIZADO, (funcionario_tipo_contrato_t){.clt = {.salario = 500}}, "Moquidesia", 7, 8);

    // -------------------------------------
    //   CALCULO DE PAGAMENTO DE FUNC
    // -------------------------------------
    TEST_ASSERT_EQUAL(5E3, funcionario_calcular_total_pagar_funcionario(f[0]));
    TEST_ASSERT_EQUAL(5E3, funcionario_calcular_total_pagar_funcionario(f[1]));
    TEST_ASSERT_EQUAL(7.8E3, funcionario_calcular_total_pagar_funcionario(f[2]));
    TEST_ASSERT_EQUAL(0, funcionario_calcular_total_pagar_funcionario(f[3]));
    TEST_ASSERT_EQUAL(0, funcionario_calcular_total_pagar_funcionario(f[4]));

    // -------------------------------------
    //   CALCULO DA FOLHA DE PAGAMENTO
    // -------------------------------------
    TEST_ASSERT_EQUAL(17.8E3, funcionario_calcular_folha_pagamento_dinamico(f, QTDE_FUNCIONARIO));

    // -------------------------------------
    //   DESALOCACAO DE MEMORIA
    // -------------------------------------
    funcionario_close(&f[2]);
    TEST_ASSERT_EQUAL(NULL, f[2]);
    TEST_ASSERT_EQUAL(NULL, f[3]); // usuario com contrato do tipo clt mas com a estrutura de terceirizado
    TEST_ASSERT_EQUAL(NULL, f[4]); // usuario com contrato do tipo terceirizado mas com a estrutura de clt
    TEST_ASSERT_NOT_EQUAL(NULL, f);
    TEST_ASSERT_NOT_EQUAL(NULL, f[0]);
    TEST_ASSERT_NOT_EQUAL(NULL, f[1]);

    funcionario_close_all(&f, QTDE_FUNCIONARIO);
    TEST_ASSERT_EQUAL(NULL, f);
}

void teste_cadastro_estatico_funcionario()
{
    funcionario_t f[QTDE_FUNCIONARIO];

    // -------------------------------------
    //   CADASTRO
    // -------------------------------------
    funcionario_init_estatico(&f[0], FUNCIONARIO_CONTRATO_TERCEIRIZADO, (funcionario_tipo_contrato_t){.terceirizado = {.valor_por_hora = 50, .horas_trabalhadas = 100}}, "Joao", 0, 0);
    funcionario_init_estatico(&f[1], FUNCIONARIO_CONTRATO_CLT, (funcionario_tipo_contrato_t){.clt = {.salario = 3000}}, "Marcela", 10, 200);
    funcionario_init_estatico(&f[2], FUNCIONARIO_CONTRATO_TERCEIRIZADO, (funcionario_tipo_contrato_t){.terceirizado = {.valor_por_hora = 30, .horas_trabalhadas = 180}}, "Joaquim", 12, 200);
    funcionario_init_estatico(&f[3], FUNCIONARIO_CONTRATO_CLT, (funcionario_tipo_contrato_t){.terceirizado = {.valor_por_hora = 10, .horas_trabalhadas = 5}}, "Matheus", 5, 6);
    funcionario_init_estatico(&f[4], FUNCIONARIO_CONTRATO_TERCEIRIZADO, (funcionario_tipo_contrato_t){.clt = {.salario = 500}}, "Moquidesia", 7, 8);

    // -------------------------------------
    //   CALCULO DE PAGAMENTO DE FUNC
    // -------------------------------------
    TEST_ASSERT_EQUAL(5E3, funcionario_calcular_total_pagar_funcionario(&f[0]));
    TEST_ASSERT_EQUAL(5E3, funcionario_calcular_total_pagar_funcionario(&f[1]));
    TEST_ASSERT_EQUAL(7.8E3, funcionario_calcular_total_pagar_funcionario(&f[2]));
    TEST_ASSERT_EQUAL(0, funcionario_calcular_total_pagar_funcionario(&f[3]));
    TEST_ASSERT_EQUAL(0, funcionario_calcular_total_pagar_funcionario(&f[4]));

    // -------------------------------------
    //   CALCULO DA FOLHA DE PAGAMENTO
    // -------------------------------------
    TEST_ASSERT_EQUAL(17.8E3, funcionario_calcular_folha_pagamento_estatico(f, QTDE_FUNCIONARIO));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(teste_cadastro_dinamico_funcionario);
    RUN_TEST(teste_cadastro_estatico_funcionario);
    return UNITY_END();
}
