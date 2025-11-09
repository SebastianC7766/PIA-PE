
Simulación modular de monitoreo de temperatura por zonas en un invernadero.  
Cada zona registra su temperatura, controla automáticamente su ventilador dependiendo de un umbral configurado, y genera un historial de eventos.

---

## 👥 Integrantes
| Nombre | Matrícula |
|-------|-----------|
| Cesar Yahir Alonso Reyes | 2069375 |
| Sebastian Calderon Carrillo | 2087472 |

---

## 🎯 Objetivo

Aplicar conceptos de programación estructurada:
- Estructuras
- Punteros y memoria dinámica
- Manejo de archivos binarios
- Modularidad
- Simulación mediante consola
- Registro cronológico de eventos automáticos

---

## 📂 Estructura del Proyecto

| Archivo | Descripción |
|--------|-------------|
| `main.c` | Contiene el menú principal y navegación. |
| `zonas.c` | Manejo de registro y almacenamiento de zonas (`zonas.dat`). |
| `temp.c` | Control de temperatura, ventiladores y registro de eventos (`eventos.dat`). |
| `users.c` | Módulo de usuarios (`users.dat`). |

---

## 🏗️ Funcionalidades por Módulo

### `zonas.c`
- Registrar nuevas zonas
- Validar IDs para evitar duplicados
- Cargar zonas desde archivo binario
- Guardar automáticamente cada nueva zona

### `temp.c`
- Actualización automática de temperatura simulada
- Activación/desactivación automática de ventilador según umbral
- Control manual del ventilador
- Registro cronológico en `eventos.dat`
- Simulación en tiempo real (actualiza cada 3s)

---

## 📊 Grafica de Menús

```
 ┌─────────────────┐
 │   INICIO        │
 └───────┬─────────┘
         │
         ▼
 ┌───────────────────────┐
 │ Mostrar Menú Principal│
 └───────┬───────────────┘
         │
         │ OPCIÓN
         ▼
 ┌───────────────┬───────────────────────────┬──────────────────────┬──────────────────┬──────────┐
 │1: Zonas       │2: Control de Temperatura  │    3: Consultas      │ 4: Configuración │ 5: Salir │
 └────┬──────────┴─────────┬─────────────────┴──────────┬───────────┴───────┬──────────┴─────┬────┘
      │                    │                            │                   │                │
      ▼                    ▼                            ▼                   ▼                ▼
 (Submenú Zonas)    (Submenú Control Temp.)      (Submenú Consultas)   (Submenú Config.)     FIN
 ```

---

## 🧱 Archivos Generados

| Archivo | Tipo | Contenido |
|--------|------|-----------|
| `zonas.dat` | binario | Zonas registradas |
| `eventos.dat` | binario | Historial de temperatura y estado del ventilador |

---

## 🚀 Compilación y Ejecución
Nota: Este proyecto usa windows.h y conio.h, se recomiendo compilar en Windows o adaptar llamadas (Sleep, kbhit).

```bash
gcc main.c -o invernadero
./invernadero