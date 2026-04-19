"use client"

import { useState, useRef, useEffect } from "react"
import { Bot, Send, Paperclip, BadgeCheck } from "lucide-react"
import { Input } from "@/components/ui/input"
import { Button } from "@/components/ui/button"
import { cn } from "@/lib/utils"
import Image from "next/image"

interface Message {
  id: string
  type: "user" | "assistant"
  content: string
  timestamp: string
  card?: {
    title: string
    description: string
    alternatives?: Array<{
      name: string
      lab: string
      price: string
    }>
    note?: string
  }
}

const initialMessages: Message[] = [
  {
    id: "1",
    type: "assistant",
    content:
      "Olá! Sou o seu Assistente da Apothecary. Como posso ajudar com as suas questões sobre medicamentos hoje? Posso verificar dosagens, sugerir alternativas genéricas ou localizar farmácias com stock em Luanda.",
    timestamp: "09:41",
  },
]

const suggestedActions = [
  "Onde encontrar em Luanda?",
  "Quais os efeitos secundários?",
  "Pode ser tomado com Ibuprofeno?",
  "Ver bula completa",
]

export default function SuportePage() {
  const [messages, setMessages] = useState<Message[]>(initialMessages)
  const [inputValue, setInputValue] = useState("")
  const [isTyping, setIsTyping] = useState(false)
  const messagesEndRef = useRef<HTMLDivElement>(null)

  const scrollToBottom = () => {
    messagesEndRef.current?.scrollIntoView({ behavior: "smooth" })
  }

  useEffect(() => {
    scrollToBottom()
  }, [messages])

  const handleSend = () => {
    if (!inputValue.trim()) return

    const userMessage: Message = {
      id: Date.now().toString(),
      type: "user",
      content: inputValue,
      timestamp: new Date().toLocaleTimeString("pt-AO", { hour: "2-digit", minute: "2-digit" }),
    }

    setMessages((prev) => [...prev, userMessage])
    setInputValue("")
    setIsTyping(true)

    // Simulate AI response
    setTimeout(() => {
      const assistantMessage: Message = {
        id: (Date.now() + 1).toString(),
        type: "assistant",
        content:
          "Para um adulto de 75kg, a dosagem padrão de Paracetamol é geralmente de 500mg a 1000mg a cada 4 a 6 horas. Não exceda 4000mg (4g) num período de 24 horas.",
        timestamp: new Date().toLocaleTimeString("pt-AO", { hour: "2-digit", minute: "2-digit" }),
        card: {
          title: "Informação de Dosagem:",
          description:
            "Para um adulto de 75kg, a dosagem padrão de Paracetamol é geralmente de 500mg a 1000mg a cada 4 a 6 horas. Não exceda 4000mg (4g) num período de 24 horas.",
          alternatives: [
            { name: "Genérico A", lab: "Laboratórios Angola", price: "850 Kz" },
            { name: "Paracetam-L", lab: "Pharma Local", price: "920 Kz" },
          ],
          note: "Esta informação é meramente informativa. Consulte sempre um farmacêutico ou médico antes de iniciar qualquer medicação.",
        },
      }

      setMessages((prev) => [...prev, assistantMessage])
      setIsTyping(false)
    }, 1500)
  }

  const handleSuggestedAction = (action: string) => {
    setInputValue(action)
  }

  return (
    <div className="flex flex-col h-[calc(100vh-4rem)] max-w-5xl mx-auto">
      {/* Chat Area */}
      <section className="flex-1 overflow-y-auto pt-8 pb-48 px-6 flex flex-col gap-8">
        {/* Date Divider */}
        <div className="flex justify-center">
          <span className="px-4 py-1 bg-muted text-muted-foreground text-xs rounded-full font-medium">
            Hoje
          </span>
        </div>

        {/* Messages */}
        {messages.map((message) => (
          <div
            key={message.id}
            className={cn(
              "flex gap-4 items-start max-w-[85%]",
              message.type === "user" && "self-end flex-row-reverse"
            )}
          >
            {/* Avatar */}
            {message.type === "assistant" ? (
              <div className="w-10 h-10 rounded-xl bg-primary flex items-center justify-center flex-shrink-0">
                <Bot className="w-5 h-5 text-primary-foreground" />
              </div>
            ) : (
              <div className="w-10 h-10 rounded-xl overflow-hidden flex-shrink-0">
                <Image
                  src="https://images.unsplash.com/photo-1472099645785-5658abf4ff4e?w=100&h=100&fit=crop&crop=face"
                  alt="User Avatar"
                  width={40}
                  height={40}
                  className="w-full h-full object-cover"
                />
              </div>
            )}

            {/* Message Content */}
            <div
              className={cn(
                "flex flex-col gap-2",
                message.type === "user" && "items-end"
              )}
            >
              {message.card ? (
                <div className="bg-muted text-foreground p-6 rounded-2xl rounded-tl-sm shadow-sm space-y-4">
                  <p className="font-medium text-primary">{message.card.title}</p>
                  <p>{message.card.description}</p>

                  {message.card.alternatives && (
                    <div className="bg-card rounded-xl p-4 flex flex-col gap-3 border border-border/10">
                      <p className="text-sm font-bold flex items-center gap-2">
                        <BadgeCheck className="w-4 h-4 text-tertiary" />
                        Alternativas Genericas Sugeridas
                      </p>
                      <div className="grid grid-cols-1 sm:grid-cols-2 gap-3">
                        {message.card.alternatives.map((alt, index) => (
                          <div
                            key={index}
                            className="bg-muted p-3 rounded-lg flex justify-between items-center"
                          >
                            <div>
                              <p className="text-xs font-bold text-foreground">{alt.name}</p>
                              <p className="text-[11px] text-muted-foreground">{alt.lab}</p>
                            </div>
                            <span className="text-tertiary font-bold text-sm">{alt.price}</span>
                          </div>
                        ))}
                      </div>
                    </div>
                  )}

                  {message.card.note && (
                    <p className="text-xs italic text-muted-foreground border-l-2 border-primary/20 pl-3">
                      Nota: {message.card.note}
                    </p>
                  )}
                </div>
              ) : (
                <div
                  className={cn(
                    "p-5 rounded-2xl shadow-sm leading-relaxed",
                    message.type === "assistant"
                      ? "bg-muted text-foreground rounded-tl-sm"
                      : "bg-primary text-primary-foreground rounded-tr-sm"
                  )}
                >
                  {message.content}
                </div>
              )}
              <span className="text-[10px] text-muted-foreground font-medium px-1">
                {message.timestamp}
              </span>
            </div>
          </div>
        ))}

        {/* Typing Indicator */}
        {isTyping && (
          <div className="flex gap-4 items-start max-w-[85%]">
            <div className="w-10 h-10 rounded-xl bg-primary flex items-center justify-center flex-shrink-0">
              <Bot className="w-5 h-5 text-primary-foreground" />
            </div>
            <div className="bg-muted p-5 rounded-2xl rounded-tl-sm">
              <div className="flex gap-1">
                <div className="w-2 h-2 bg-muted-foreground rounded-full animate-bounce" />
                <div className="w-2 h-2 bg-muted-foreground rounded-full animate-bounce [animation-delay:0.1s]" />
                <div className="w-2 h-2 bg-muted-foreground rounded-full animate-bounce [animation-delay:0.2s]" />
              </div>
            </div>
          </div>
        )}

        <div ref={messagesEndRef} />
      </section>

      {/* Input Bar */}
      <div className="fixed bottom-[72px] md:bottom-0 right-0 left-0 md:left-64 bg-white/90 dark:bg-slate-900/90 backdrop-blur-2xl px-4 md:px-6 pt-4 pb-6 border-t border-transparent shadow-[0_-10px_30px_rgba(0,0,0,0.03)] z-40">
        {/* Suggested Actions */}
        <div className="md:max-w-2xl mr-16 md:mx-auto mb-4 flex flex-wrap gap-2 h-[34px] overflow-hidden">
          {suggestedActions.map((action) => (
            <button
              key={action}
              onClick={() => handleSuggestedAction(action)}
              className="whitespace-nowrap px-4 py-2 bg-secondary text-secondary-foreground text-[11px] md:text-xs rounded-full font-semibold hover:opacity-90 transition-all flex-shrink-0"
            >
              {action}
            </button>
          ))}
        </div>

        {/* Input Box */}
        <div className="md:max-w-2xl mr-16 md:mx-auto relative group">
          <Input
            type="text"
            value={inputValue}
            onChange={(e) => setInputValue(e.target.value)}
            onKeyDown={(e) => e.key === "Enter" && handleSend()}
            placeholder="Pergunte sobre medicamentos ou dosagens..."
            className="w-full bg-muted border-none rounded-2xl h-14 pl-5 pr-24 text-sm"
          />
          <div className="absolute right-1.5 top-1/2 -translate-y-1/2 flex items-center gap-1">
            <button className="p-2 text-muted-foreground hover:text-primary transition-colors">
              <Paperclip className="w-4 h-4" />
            </button>
            <Button
              onClick={handleSend}
              disabled={!inputValue.trim()}
              className="w-11 h-11 rounded-xl shadow-md p-0 flex items-center justify-center"
            >
              <Send className="w-4 h-4" />
            </Button>
          </div>
        </div>
      </div>
    </div>
  )
}
